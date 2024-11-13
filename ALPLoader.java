// load ALP program

import java.util.ArrayList;
import java.util.Scanner;

public class ALPLoader {
    // Define memory size for main memory
    private static final int MEMORY_SIZE = 256;
    // Main memory to store instructions
    private static ArrayList<String> mainMemory = new ArrayList<>(MEMORY_SIZE);

    public static void loadALPToMemory() {
        Scanner scanner = new Scanner(System.in);
        int memoryPointer = 0; // Pointer to keep track of memory addresses

        System.out.println("Enter ALP instructions (type 'END' to stop):");

        while (true) {
            System.out.print("Instruction " + memoryPointer + ": ");
            String instruction = scanner.nextLine().trim();

            // Stop if the user types "END"
            if (instruction.equalsIgnoreCase("END")) {
                break;
            }

            // Check if memory is full
            if (memoryPointer >= MEMORY_SIZE) {
                System.out.println("Error: Main memory is full. Program exceeds available memory.");
                break;
            }

            // Add the instruction to main memory
            mainMemory.add(instruction);
            System.out.println("Loaded '" + instruction + "' into memory address " + memoryPointer);
            memoryPointer++;
        }

        System.out.println("\nProgram successfully loaded into main memory.");
    }

    public static void displayMemory() {
        System.out.println("\nMain Memory Contents:");
        for (int i = 0; i < mainMemory.size(); i++) {
            System.out.println("Memory Address " + i + ": " + mainMemory.get(i));
        }
    }

    public static void main(String[] args) {
        loadALPToMemory(); // Load the ALP program from console input
        displayMemory(); // Display the contents of main memory
    }
}

// MOV A, 5
// ADD B, A
// SUB C, B
// STORE A, 100
// LOAD B, C
// END