#!/bin/bash

TEST_DIR="tests"
OUT_DIR="out"
test_number=0
passed_tests=0
failed_tests=0

mkdir -p $OUT_DIR

FILES=($TEST_DIR/t{1..5}.txt $TEST_DIR/bytes{1..5}.txt)

FLAGS=("b" "e" "n" "s" "t" "v" "E" "T")
LONG_FLAGS=("" "--number-nonblank" "--number" "--squeeze-blank")

generate_combinations() {
    local elements=("$@")
    local combinations=()
    for ((i = 0; i < (1 << ${#elements[@]}); ++i)); do
        combination=""
        for ((j = 0; j < ${#elements[@]}; ++j)); do
            ((i & (1 << j))) && combination+="${elements[j]}"
        done
        combinations+=("$combination")
    done
    echo "${combinations[@]}"
}

run_mem_test() {
  valgrind_output=$(mktemp)
  valgrind --leak-check=full --error-exitcode=1 $1 &> "$valgrind_output"
  if grep -q "definitely lost: [^0]" "$valgrind_output"; then
      memleak_count=$((memleak_count + 1))
      echo "Memory leak detected for: $1" >> $OUT_DIR/memleak.txt
  fi
  if grep -q "indirectly lost: [^0]" "$valgrind_output"; then
      memleak_count=$((memleak_count + 1))
      echo "Memory leak detected for: $1" >> $OUT_DIR/memleak.txt
  fi
  if grep -q "possibly lost: [^0]" "$valgrind_output"; then
      memleak_count=$((memleak_count + 1))
      echo "Memory leak detected for: $1" >> $OUT_DIR/memleak.txt
  fi
  if grep -q "still reachable: [^0]" "$valgrind_output"; then
      memleak_count=$((memleak_count + 1))
      echo "Memory leak detected for: $1" >> $OUT_DIR/memleak.txt
  fi
  if grep -q "suppressed: [^0]" "$valgrind_output"; then
      memleak_count=$((memleak_count + 1))
      echo "Memory leak detected for: $1" >> $OUT_DIR/memleak.txt
  fi
  if grep -q "Invalid write of size" "$valgrind_output"; then
      memleak_count=$((memleak_count + 1))
      echo "Invalid write of size: $1" >> $OUT_DIR/memleak.txt
  fi
  if grep -q "Invalid read of size" "$valgrind_output"; then
      memleak_count=$((memleak_count + 1))
      echo "Invalid read of size: $1" >> $OUT_DIR/memleak.txt
  fi
  if grep -q "ERROR SUMMARY: [^0]" "$valgrind_output"; then
      memleak_count=$((memleak_count + 1))
      echo "ERROR SUMMARY FOR: $1" >> $OUT_DIR/memleak.txt
  fi
  rm "$valgrind_output"
  if [[ $memleak_count -gt 0 ]]; then
    echo "Memory leaks occured in $memleak_count calls. Check $OUT_DIR/memleak.txt for info."
    exit
  fi
}


COMBINATIONS=($(generate_combinations "${FLAGS[@]}"))

> $OUT_DIR/log.txt

for long_flag in "${LONG_FLAGS[@]}"; do
    for combination in "${COMBINATIONS[@]}"; do
        for file in "${FILES[@]}"; do
            command="./s21_cat -$combination $long_flag $file > $OUT_DIR/out1.txt"
            echo "$command"
            eval $command
            
            command_cat="cat -$combination $long_flag $file > $OUT_DIR/out2.txt"
            eval $command_cat
            
            if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
                echo "FAILED: $command" >> $OUT_DIR/log.txt
                failed_tests=$((failed_tests + 1))
            else
                passed_tests=$((passed_tests + 1))
            fi
            test_number=$((test_number + 1))
        done
        
        command="./s21_cat -$combination $long_flag ${FILES[*]} > $OUT_DIR/out1.txt"
        echo "$command"
        # run_mem_test "$command"
        eval $command
        
        command_cat="cat -$combination $long_flag ${FILES[*]} > $OUT_DIR/out2.txt"
        eval $command_cat

        
        if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
            echo "FAILED: $command" >> $OUT_DIR/log.txt
            failed_tests=$((failed_tests + 1))
        else 
            passed_tests=$((passed_tests + 1))
        fi
        test_number=$((test_number + 1))
    done
done

echo "======================================================================"
if [[ -s $OUT_DIR/log.txt ]]; then
    echo "Некоторые тесты не пройдены. Подробности в $OUT_DIR/log.txt."
else
    echo "Все тесты успешно пройдены!"
fi
echo "Total tests: $test_number"
echo "Passed tests: $passed_tests"
echo "Failed tests: $failed_tests"
