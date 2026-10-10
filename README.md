# Worklet 1 — Team Development and Integration Guide

## 1. Purpose of This README

This README explains how each team member should develop their assigned worklets and integrate their code with the main project.

The project is divided into Field, Vector, Matrix, Matrix Classification, and Testing/Integration components. Each team member should work on their assigned files without overwriting another member's implementation.

**Important:** Before starting, agree on the function names, parameters, return types, and responsibilities declared in the shared header files.

## 2. Project Folder Structure

Maintain the following structure:

```text
Worlet_1_test/
├── include/
│   ├── field.h
│   ├── vector.h
│   ├── matrix.h
│   └── matrix_types.h
├── src/
│   ├── field.c
│   ├── vector.c
│   ├── matrix.c
│   ├── matrix_types.c
│   └── main.c
├── tests/
│   ├── test_worklet1.c
│   └── test_matrix_types.c
├── build/
├── Makefile
└── README.md
```

Do not create separate copies of the entire project for each worklet. Everyone should contribute to the same agreed project structure.

## 3. Work Allocation and Instructions

### Member 1 — Field Worklets (`F01–F16`)

**Files to work on:**
- `include/field.h`
- `src/field.c`

**What to do:**

1. Define the `FieldElement` structure.
2. Implement validation for the prime modulus.
3. Implement initialization and normalization of field elements.
4. Implement field addition, subtraction, and multiplication.
5. Implement multiplicative inverse and equality checking.
6. Handle invalid inputs and edge cases.
7. Make sure all functions match their declarations in `field.h`.

The field module is the foundation for Vector and Matrix, so it must be integrated first.

**Before handing over your work:**

- Ensure all required function declarations are present in `field.h`.
- Include appropriate headers.
- Test valid and invalid inputs.
- Provide the final versions of `field.h` and `field.c`.
- Tell the integration member which functions are implemented and any known limitations.

### Member 2 — Vector Worklets (`V01–V15`)

**Files to work on:**
- `include/vector.h`
- `src/vector.c`

**What to do:**

1. Define the vector representation required by your assigned worklets.
2. Implement the vector operations specified in the assignment.
3. Use the Field API for field-element operations where required.
4. Validate vector sizes and any operation-specific constraints.
5. Handle invalid inputs and memory allocation failures.
6. Provide appropriate initialization and cleanup functions.
7. Ensure function declarations in `vector.h` match definitions in `vector.c`.

**Dependency:** Your code must use the agreed Field interface. Do not independently redefine `FieldElement` or duplicate the Field implementation.

**Before handing over your work:**

- Provide `vector.h` and `vector.c`.
- List the implemented functions.
- Explain how vectors are initialized and freed.
- Include example inputs and expected outputs.
- Mention any assumptions or limitations.

### Member 3 — Matrix Worklets (`M01–M17`)

**Files to work on:**
- `include/matrix.h`
- `src/matrix.c`

**What to do:**

1. Define the Matrix structure according to the agreed interface.
2. Implement matrix initialization and cleanup.
3. Implement element access.
4. Implement matrix addition.
5. Implement scalar multiplication.
6. Implement matrix transpose.
7. Implement matrix multiplication.
8. Implement matrix equality checking.
9. Validate dimensions, moduli, and invalid inputs.
10. Handle memory allocation failures and prevent invalid memory access.

Implement only the functions assigned by the Matrix worklet specification; the list above describes the current project's expected Matrix API.

**Dependency:** Matrix operations must use the shared Field representation and respect the agreed finite-field arithmetic rules.

**Before handing over your work:**

- Provide `matrix.h` and `matrix.c`.
- Ensure declarations and definitions match.
- Explain the matrix memory layout and cleanup requirements.
- Test compatible and incompatible dimensions.
- Provide sample inputs and expected results.

### Member 4 — Matrix Classification

**Files to work on:**
- `include/matrix_types.h`
- `src/matrix_types.c`

This responsibility must be explicitly assigned to one member. If the Matrix teammate owns classification, the Testing/Integration member should not independently edit these files.

**What to do:**

Implement functions to identify whether a matrix is:

1. Square
2. Zero
3. Diagonal
4. Identity
5. Scalar
6. Symmetric
7. Upper triangular
8. Lower triangular

The classification functions must use the agreed Matrix representation and must not modify the matrix merely to classify it.

**Before handing over your work:**

- Provide both classification files.
- Test each classification separately.
- Test matrices that satisfy several classifications simultaneously.
- Test rectangular matrices and 1×1 matrices.
- Ensure your code uses the existing Matrix API consistently.

### Member 5 — Testing and Integration (My Responsibility)

**Files I maintain:**
- `tests/test_worklet1.c`
- `tests/test_matrix_types.c`
- `Makefile`
- `README.md`

I will also coordinate the integration of the implementation files supplied by the other members.

**What I will do:**

1. Review the header files and ensure the APIs are consistent.
2. Integrate the Field, Vector, and Matrix implementations.
3. Configure the Makefile to compile the required source files.
4. Write and maintain unit tests for the available functions.
5. Write integration tests that verify components work together.
6. Run regression tests after changes.
7. Check compiler warnings and errors.
8. Run sanitizers if the target is configured.
9. Report failures to the responsible member with the failing test and expected result.

**Important:** The tests should call functions through their public headers. I will not copy the implementation of another member's module into the test files.

## 4. How the Components Connect

The intended dependency structure is:

```text
Field
  ├── Vector
  └── Matrix
        └── Matrix Classification

Testing and Integration
  └── Tests each module and checks their interactions
```

Follow this integration order:

1. Integrate and verify Field.
2. Integrate Vector using the Field API.
3. Integrate Matrix using the Field API.
4. Integrate Matrix Classification using the Matrix API.
5. Run all unit and integration tests.
6. Fix failures and rerun regression tests.

## 5. Rules Everyone Must Follow

### Rule 1 — Keep headers and implementations consistent

Function declarations belong in `.h` files, and implementations belong in `.c` files.

For example, if `field.h` declares:

```c
bool field_is_prime(long p);
```

then `field.c` must implement that same function with a compatible signature.

### Rule 2 — Do not overwrite another member's files

Only the assigned owner should make routine changes to a module. If a shared interface needs to change, discuss it with the affected members first.

### Rule 3 — Do not add extra `main()` functions to implementation files

The application and test programs are separate executables. Do not paste a test program into `field.c`, `vector.c`, or `matrix.c`.

### Rule 4 — Use the existing public API

A module should call another module through its header and public functions. Do not directly duplicate its internal implementation.

### Rule 5 — Communicate before changing function signatures

Changing a parameter, return type, function name, or data structure can break another member's code and the tests.

### Rule 6 — Handle memory responsibly

If a function successfully initializes or allocates an object, follow the documented ownership and cleanup rules. Report allocation failures instead of using invalid memory.

## 6. What to Send for Integration

Every implementation member should provide:

- The final `.h` file.
- The corresponding `.c` file.
- A list of implemented functions.
- A brief description of how to call the functions.
- Sample input and expected output.
- Any known limitations or unimplemented requirements.
- Confirmation that their module compiles, if tested.

Do not send only screenshots of code. Send the actual source files so they can be compiled and integrated.

## 7. Build and Test Commands

Run the following commands from the project root after integration.

### Clean previous build files

```bash
make clean
```

### Compile the project

```bash
make all
```

### Run the test suites

```bash
make test
```

### Run the interactive application

```bash
make run
```

If the `sanitize` target exists, run:

```bash
make sanitize
```

Then rebuild and test normally:

```bash
make clean
make all
make test
```

A successful compilation does not automatically mean all tests pass. Review the test output and any compiler warnings.

## 8. Definition of Done

A module is ready for integration when:

- [ ] Its assigned functionality is implemented.
- [ ] Its header and source file are consistent.
- [ ] Required input validation is included.
- [ ] Memory allocation and cleanup are handled correctly.
- [ ] The code compiles with the project compiler flags.
- [ ] Relevant unit tests pass.
- [ ] Its owner has documented limitations and assumptions.

The complete project is ready for submission when:

- [ ] All assigned modules have been integrated.
- [ ] `make all` succeeds.
- [ ] `make test` succeeds.
- [ ] Integration and regression tests have been run.
- [ ] Compiler warnings have been reviewed.
- [ ] The README and final source files match the submitted project.

## 9. Final Note

Each member is responsible for implementing and testing their assigned component. The Testing/Integration member coordinates the shared interfaces, combines the modules, and verifies that the complete project works correctly.

**Please complete your assigned files, preserve the agreed interfaces, and communicate any changes before integration.**