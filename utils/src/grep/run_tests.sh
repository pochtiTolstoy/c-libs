#!/bin/bash

TEST_DIR="tests"
PATTERN_DIR="patterns"
OUT_DIR="out"
STRING_TO_SEARCH=("SAFETY" "^int" "INCLUDE" "\"=>\"" "\"{\|}\"" "\"[0-2]\|[4-6]\"")
test_number=0
passed_tests=0
failed_tests=0
memleak_count=0
fast_quit=1

mkdir -p $OUT_DIR

FILES=($TEST_DIR/t{1..5}.txt $TEST_DIR/empty.txt)
PATTERN_FILES=($PATTERN_DIR/p{1..3}.pt)
FLAGS_E=("s" "h" "i" "v" "c" "l" "n" "e" " ")
FLAGS_F=("s" "h" "i" "v" "c" "l" "n" "f" " ")
FLAGS_NO_EF=("s" "h" "i" "v" "c" "l" "n" "o")

generate_combinations() {
    local elements=("$@")
    local combinations=()
    local combination=""
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
  return
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

> $OUT_DIR/log.txt
> $OUT_DIR/memleak.txt

run_test_no_ef_flags() {
    COMBINATIONS_NO_EF=($(generate_combinations "${FLAGS_NO_EF[@]}"))
    for pattern in "${STRING_TO_SEARCH[@]}"; do
        for combination in "${COMBINATIONS_NO_EF[@]}"; do
            for file in "${FILES[@]}"; do
                command="./s21_grep $pattern -$combination $file > $OUT_DIR/out1.txt"
                echo "$command"
                run_mem_test "$command"
                eval $command
                
                command_grep="grep $pattern -$combination $file > $OUT_DIR/out2.txt"
                eval $command_grep
                
                if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
                    echo "FAILED: $command" >> $OUT_DIR/log.txt
                    failed_tests=$((failed_tests + 1))
                    if [[ $fast_quit -eq 1 ]]; then
                      exit
                    fi
                else
                    passed_tests=$((passed_tests + 1))
                fi
                test_number=$((test_number + 1))
            done
        done
    done
}

run_main_test_e() {
    combinations=($(generate_combinations "${FLAGS_NO_EF[@]}"))
    echo "${combinations[@]}"
    for pattern in "${STRING_TO_SEARCH[@]}"; do
        for combination in "${combinations[@]}"; do
            combination+=e
            for file in "${FILES[@]}"; do
                command="./s21_grep -$combination $pattern $file > $OUT_DIR/out1.txt"
                echo "$command"
                eval $command
                
                command_grep="grep -$combination $pattern $file > $OUT_DIR/out2.txt"
                eval $command_grep
                
                if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
                    echo "FAILED: $command" >> $OUT_DIR/log.txt
                    failed_tests=$((failed_tests + 1))
                    if [[ $fast_quit -eq 1 ]]; then
                      exit
                    fi
                else
                    passed_tests=$((passed_tests + 1))
                fi
                test_number=$((test_number + 1))
            done

    # TEST: multiflag combinations
            command="./s21_grep -$combination $pattern ${FILES[*]} > $OUT_DIR/out1.txt"
            echo "$command"
            eval $command
            run_mem_test "$command"
            
            command_grep="grep -$combination $pattern ${FILES[*]} > $OUT_DIR/out2.txt"
            eval $command_grep
            
            if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
                echo "FAILED: $command" >> $OUT_DIR/log.txt
                failed_tests=$((failed_tests + 1))
                    if [[ $fast_quit -eq 1 ]]; then
                      exit
                    fi
            else 
                passed_tests=$((passed_tests + 1))
            fi
            test_number=$((test_number + 1))

    # TEST: single flags combinations
            new_combination=""
            for (( i=0; i<${#combination}; i++ )); do
            new_combination+="-${combination:i:1} "
            done
            new_combination=${new_combination% }

            command="./s21_grep $new_combination $pattern ${FILES[*]} > $OUT_DIR/out1.txt"
            eval $command
            echo "$command"
            run_mem_test "$command"

            command_grep="grep $new_combination $pattern ${FILES[*]} > $OUT_DIR/out2.txt"
            eval $command_grep

            if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
                echo "FAILED: $command" >> $OUT_DIR/log.txt
                failed_tests=$((failed_tests + 1))
                    if [[ $fast_quit -eq 1 ]]; then
                      exit
                    fi
            else 
                passed_tests=$((passed_tests + 1))
            fi
            test_number=$((test_number + 1))
        done
    done
}

run_main_test_f() {
    combinations=($(generate_combinations "${FLAGS_NO_EF[@]}"))
    for pattern in "${PATTERN_FILES[@]}"; do
        for combination in "${combinations[@]}"; do
            combination+=f
            for file in "${FILES[@]}"; do
                command="./s21_grep -$combination $pattern $file > $OUT_DIR/out1.txt"
                echo "$command"
                eval $command
                
                command_grep="grep -$combination $pattern $file > $OUT_DIR/out2.txt"
                eval $command_grep
                
                if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
                    echo "FAILED: $command" >> $OUT_DIR/log.txt
                    failed_tests=$((failed_tests + 1))
                    if [[ $fast_quit -eq 1 ]]; then
                      exit
                    fi
                else
                    passed_tests=$((passed_tests + 1))
                fi
                test_number=$((test_number + 1))
            done

    # TEST: multiflag combinations
            command="./s21_grep -$combination $pattern ${FILES[*]} > $OUT_DIR/out1.txt"
            echo "$command"
            eval $command
            run_mem_test "$command"
            
            command_grep="grep -$combination $pattern ${FILES[*]} > $OUT_DIR/out2.txt"
            eval $command_grep
            
            if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
                echo "FAILED: $command" >> $OUT_DIR/log.txt
                failed_tests=$((failed_tests + 1))
                    if [[ $fast_quit -eq 1 ]]; then
                      exit
                    fi
            else 
                passed_tests=$((passed_tests + 1))
            fi
            test_number=$((test_number + 1))

    # TEST: single flags combinations
            new_combination=""
            for (( i=0; i<${#combination}; i++ )); do
            new_combination+="-${combination:i:1} "
            done
            new_combination=${new_combination% }

            command="./s21_grep $new_combination $pattern ${FILES[*]} > $OUT_DIR/out1.txt"
            eval $command
            echo "$command"
            run_mem_test "$command"

            command_grep="grep $new_combination $pattern ${FILES[*]} > $OUT_DIR/out2.txt"
            eval $command_grep

            if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
                echo "FAILED: $command" >> $OUT_DIR/log.txt
                failed_tests=$((failed_tests + 1))
                    if [[ $fast_quit -eq 1 ]]; then
                      exit
                    fi
            else 
                passed_tests=$((passed_tests + 1))
            fi
            test_number=$((test_number + 1))
        done
    done
}

run_e_flags() {
  combination=""
  for (( i=0; i<${#STRING_TO_SEARCH[@]}; i++ )); do
    combination+="-e ${STRING_TO_SEARCH[i]} "
  done
  combination=${combination% }
  command="./s21_grep $combination ${FILES[*]} > $OUT_DIR/out1.txt"
  echo "$command"
  eval $command
  run_mem_test "$command"

  command_grep="grep $combination ${FILES[*]} > $OUT_DIR/out2.txt"
  eval $command_grep

  if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
  echo "FAILED: $command" >> $OUT_DIR/log.txt
  failed_tests=$((failed_tests + 1))
                    if [[ $fast_quit -eq 1 ]]; then
                      exit
                    fi
  else 
  passed_tests=$((passed_tests + 1))
  fi
  test_number=$((test_number + 1))
}

run_f_flags() {
  combination=""
  for (( i=0; i<${#PATTERN_FILES[@]}; i++ )); do
    combination+="-f ${PATTERN_FILES[i]} "
  done
  combination=${combination% }
  command="./s21_grep $combination ${FILES[*]} > $OUT_DIR/out1.txt"
  echo "$command"
  eval $command
  run_mem_test "$command"

  command_grep="grep $combination ${FILES[*]} > $OUT_DIR/out2.txt"
  eval $command_grep

  if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
  echo "FAILED: $command" >> $OUT_DIR/log.txt
  failed_tests=$((failed_tests + 1))
                    if [[ $fast_quit -eq 1 ]]; then
                      exit
                    fi
  else 
  passed_tests=$((passed_tests + 1))
  fi
  test_number=$((test_number + 1))
}

run_ef_flags() {
  combination=""
  for (( i=0; i<${#PATTERN_FILES[@]}; i++ )); do
    combination+="-f ${PATTERN_FILES[i]} "
  done
  for (( i=0; i<${#STRING_TO_SEARCH[@]}; i++ )); do
    combination+="-e ${STRING_TO_SEARCH[i]} "
  done
  combination=${combination% }
  command="./s21_grep $combination ${FILES[*]} > $OUT_DIR/out1.txt"
  echo "$command"
  eval $command
  run_mem_test "$command"

  command_grep="grep $combination ${FILES[*]} > $OUT_DIR/out2.txt"
  eval $command_grep

  if ! diff -q $OUT_DIR/out1.txt $OUT_DIR/out2.txt > /dev/null; then
  echo "FAILED: $command" >> $OUT_DIR/log.txt
  failed_tests=$((failed_tests + 1))
                    if [[ $fast_quit -eq 1 ]]; then
                      exit
                    fi
  else 
  passed_tests=$((passed_tests + 1))
  fi
  test_number=$((test_number + 1))
}

run_test_no_ef_flags
run_main_test_e
run_main_test_f
run_e_flags
run_f_flags
run_ef_flags

echo "======================================================================"
if [[ -s $OUT_DIR/log.txt ]]; then
    echo "Некоторые тесты не пройдены. Подробности в $OUT_DIR/log.txt."
else
    echo "Все тесты успешно пройдены!"
fi
echo "Total tests: $test_number"
echo "Passed tests: $passed_tests"
echo "Failed tests: $failed_tests"
