# determine the compiler to use for NASM

SET(ASM_DIALECT "_NASM")
SET(CMAKE_ASM${ASM_DIALECT}_COMPILER_INIT ${_CMAKE_TOOLCHAIN_PREFIX}nasm)
INCLUDE(CMakeDetermineASMCompiler)
SET(ASM_DIALECT)

