#bash programs

#!/bin/bash

# Factorial using recursion with a function
factorial() {
    if [ $1 -le 1 ]; then
        echo 1
    else
        local n=$(( $1 - 1 ))
        local result=$(factorial $n)
        echo $(( $1 * result ))
    fi
}

# Factorial without recursion
factorial_no_recursion() {
    n=$1
    result=1
    while [ $n -gt 1 ]; do
        result=$(( result * n ))
        n=$(( n - 1 ))
    done
    echo "$result"
}

# Bubble sort implementation
bubble_sort() {
    arr=("$@")
    len=${#arr[@]}
    for ((i=0; i<$len; i++)); do
        for ((j=0; j<$len-i-1; j++)); do
            if [ ${arr[$j]} -gt ${arr[$((j+1))]} ]; then
                # Swap elements
                temp=${arr[$j]}
                arr[$j]=${arr[$((j+1))]}
                arr[$((j+1))]=$temp
            fi
        done
    done
    echo "${arr[@]}"
}

# Count occurrences of a substring in a string
count_substring() {
    string=$1
    substring=$2
    count=0
    while [[ $string =~ $substring ]]; do
        ((count++))
        string=${string#*$substring}
    done
    echo "$count"
}

# Sum of digits of a number
sum_of_digits() {
    n=$1
    sum=0
    while [ $n -gt 0 ]; do
        digit=$(( n % 10 ))
        sum=$(( sum + digit ))
        n=$(( n / 10 ))
    done
    echo "$sum"
}

# Reverse digits of a number
reverse_digits() {
    n=$1
    reversed_num=0
    while [ $n -gt 0 ]; do
        digit=$(( n % 10 ))
        reversed_num=$(( reversed_num * 10 + digit ))
        n=$(( n / 10 ))
    done
    echo "$reversed_num"
}

# Armstrong number check
is_armstrong() {
    n=$1
    num_digits=${#n}
    sum_of_powers=0
    temp=$n
    while [ $temp -gt 0 ]; do
        digit=$(( temp % 10 ))
        sum_of_powers=$(( sum_of_powers + digit ** num_digits ))
        temp=$(( temp / 10 ))
    done
    if [ $sum_of_powers -eq $n ]; then
        echo "$n is an Armstrong number."
    else
        echo "$n is not an Armstrong number."
    fi
}

# Display menu
while true; do
    clear
    echo "==============================="
    echo "       Menu Driven Program"
    echo "==============================="
    echo "1. Calculate Factorial (Recursion)"
    echo "2. Calculate Factorial (Without Recursion)"
    echo "3. Bubble Sort"
    echo "4. Count Occurrences of Substring"
    echo "5. Sum of Digits"
    echo "6. Reverse Digits"
    echo "7. Armstrong Number Check"
    echo "8. Exit"
    echo "==============================="
    read -p "Enter your choice (1-8): " choice
    
    case $choice in
        1)
            read -p "Enter a number to find its factorial: " n
            echo "Factorial of $n is $(factorial $n)"
            ;;
        2)
            read -p "Enter a number to find its factorial: " n
            echo "Factorial of $n without recursion is $(factorial_no_recursion $n)"
            ;;
        3)
            read -p "Enter space-separated numbers for sorting: " -a arr
            echo "Sorted array: $(bubble_sort ${arr[@]})"
            ;;
        4)
            read -p "Enter the string: " string
            read -p "Enter the substring to count: " substring
            echo "The substring '$substring' occurs $(count_substring "$string" "$substring") times."
            ;;
        5)
            read -p "Enter a number to calculate the sum of digits: " n
            echo "The sum of digits of $n is $(sum_of_digits $n)"
            ;;
        6)
            read -p "Enter a number to reverse its digits: " n
            echo "The reversed digits of $n is $(reverse_digits $n)"
            ;;
        7)
            read -p "Enter a number to check if it's an Armstrong number: " n
            echo "$(is_armstrong $n)"
            ;;
        8)
            echo "Exiting the program. Goodbye!"
            exit 0
            ;;
        *)
            echo "Invalid choice. Please try again."
            ;;
    esac
done