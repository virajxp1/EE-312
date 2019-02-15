#!/bin/bash

. helper_files/library.sh

CPP_FILE_NAME="Project2.cpp"

wipe_after_compile()
{
    rm -rf *.o *.h *.cpp Makefile gtest library.sh
}

perform_test_on_this_submission()
{
    enable_throwing_errors

	this_dir=$(pwd)
    submission_name="${PWD##*/}"
    correct_num=0
    total_num=0
    tests=()

    cp -R "$main_dir/helper_files/"* .
    cp "$tests_dir/"* .
    if [[ $TA_MODE == true ]]; then
        make all_tests &> /dev/null || wipe_after_compile
    else
        make sample_tests || wipe_after_compile
    fi
    wipe_after_compile

    for line in $(./run_tests.out --gtest_list_tests 2> /dev/null); do
        if [[ $line == *. ]]; then
            group=$line
        else
            t=$group$line
            tests+=("$t")
        fi
    done

    for t in "${tests[@]}"; do
        total_num=$(($total_num+1))
        echo "./run_tests.out --gtest_filter=$t" | bash &> temp_output.txt && correct_num=$(($correct_num+1)) || true

        if [[ $TA_MODE == false ]]; then
            echo "after running test: $t"
            cat temp_output.txt
            echo ""
        fi
        cat temp_output.txt >> tests_output.txt
        echo "" >> tests_output.txt
    done

    rm -rf run_tests.out temp_output.txt gtest*

    echo "\"$submission_name\", \"$correct_num\", \"$total_num\"" >> "$brief_feedback_file"
}

prepare()
{
    if [[ ! -d "$main_dir/helper_files/gtest" ]]; then
        cd "$main_dir/helper_files"
        wget -O gtest.zip "https://codeload.github.com/google/googletest/zip/release-1.8.0"
        unzip gtest.zip > /dev/null
        mv "googletest-release-1.8.0" gtest
        rm gtest.zip
        cd - > /dev/null
    fi

    if [[ $TA_MODE == true ]]; then
        rm -rf test_cases
        rm -rf submissions/*.cpp
        git checkout "$tests_dir"
    else
        rm -rf "$tests_dir"/complementary_tests.cpp "$tests_dir"/tests_descriptions.txt
    fi
}

save_function clean previous_clean
clean()
{
    previous_clean
    rm -rf "$main_dir/helper_files/gtest"
}

save_function grade previous_grade
grade()
{
    if [ -f ~/.profile ]
    then
        . ~/.profile
        module load gcc &> /dev/null || true
    fi
    previous_grade
}

main "$@"
