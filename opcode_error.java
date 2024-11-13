// Opcode error in a given job

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class OpcodeChecker {
    // Define a set of valid opcodes
    private static final Set<String> VALID_OPCODES = new HashSet<>(Arrays.asList(
            "MOV", "ADD", "SUB", "STORE", "LOAD", "MUL", "DIV", "JMP", "CMP"
    // Add more valid opcodes as needed
    ));

    public static void main(String[] args) {
        // Hardcoded array of instructions
        String[] instructions = {
                "MOV A, 5",
                "ADD B, A",
                "INVALID_OP D, E" // This instruction contains an invalid opcode
        };

        System.out.println("Checking instructions for opcode errors...");

        for (int i = 0; i < instructions.length; i++) {
            String instruction = instructions[i].trim();
            System.out.println("Instruction " + (i + 1) + ": " + instruction);

            // Check if the opcode is valid
            if (!isValidOpcode(instruction)) {
                System.out.println("Opcode Error: Invalid opcode found in instruction '" + instruction + "'");
                System.out.println("Interrupt raised due to invalid opcode.");
                return; // Stop further execution if an invalid opcode is found
            }
        }

        System.out.println("All instructions are valid. No opcode errors detected.");
    }

    private static boolean isValidOpcode(String instruction) {
        // Split the instruction by space to extract the opcode
        String[] parts = instruction.split(" ");
        if (parts.length == 0) {
            return false; // Empty instruction
        }

        String opcode = parts[0]; // The first part is the opcode
        return VALID_OPCODES.contains(opcode); // Check if the opcode is in the set of valid opcodes
    }
}