FILES=$(shell find Source -not -path "Source/ThirdParty/*" -type f \( -iname "*.c" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.hpp" -o -iname "*.inl" \))

format:
    $(shell clang-format -i $(FILES))
