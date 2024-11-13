#loops in bash

#!/bin/bash

# Function for if-else statement
if_else_demo() {
    read -p "Enter your age: " age
    if (( age < 18 )); then
        echo "You are a minor."
    elif (( age <= 65 )); then
        echo "You are an adult."
    else
        echo "You are a senior."
    fi
}


# Function for for loop to print numbers from start to end
for_loop_demo() {
    read -p "Enter the start number: " start
    read -p "Enter the end number: " end
    for (( i=start; i<=end; i++ )); do
        echo "Number $i"
    done
}


# Function to check if a number is prime
is_prime() {
    local num=$1
    if (( num <= 1 )); then
        return 1
    fi
    for (( i=2; i*i<=num; i++ )); do
        if (( num % i == 0 )); then
            return 1
        fi
    done
    return 0
}


# Function for while loop demonstration (prime numbers)
while_loop_demo() {
    read -p "Enter a start number: " start
    read -p "Enter an end number: " end
    while (( start <= end )); do
        if is_prime $start; then
            echo "Prime number: $start"
        fi
        ((start++))
    done
}


# Function to calculate factorial of a number
factorial() {
    local num=$1
    local factorial=1
    local i=1
    until (( i > num )); do
        factorial=$(( factorial * i ))
        ((i++))
    done
    echo $factorial
}


# Function for until loop demonstration (factorial)
until_loop_demo() {
    read -p "Enter a number to calculate factorial: " num
    result=$(factorial $num)
    echo "Factorial of $num is $result"
}


# Display the menu
while true; do
    echo "Menu:"
    echo "1) If-Else Statement"
    echo "2) For Loop"
    echo "3) While Loop"
    echo "4) Until Loop"
    echo "5) Exit"
    read -p "Choose an option: " choice


    case $choice in
        1)
            if_else_demo
            ;;
        2)
            for_loop_demo
            ;;
        3)
            while_loop_demo
            ;;
        4)
            until_loop_demo
            ;;
        5)
            echo "Exiting..."
            break
            ;;
        *)
            echo "Invalid option, please try again."
            ;;
    esac
done
