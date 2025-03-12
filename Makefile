compiler := clang++
root_source_dir := ./src
compiler_flags := -lpthread -Werror -Wextra -Wall -pedantic -std=gnu++2b
game_of_life_src := $(root_source_dir)/game_of_life.cpp $(root_source_dir)/matrix.cpp
test_combinations_src := $(root_source_dir)/test_combinations.cpp $(root_source_dir)/matrix.cpp $(root_source_dir)/combinatorics.cpp
binaries_directory := ./Binaries
target_game := game_of_life
target_test := test_combinations

game_of_life: $(game_of_life_src)
	mkdir -p $(binaries_directory)
	@$(compiler) -O3 $(game_of_life_src) -o $(binaries_directory)/$(target_game) $(compiler_flags)
	@echo "Done"

test_combinations: $(test_combinations_src)
	mkdir -p $(binaries_directory)
	@$(compiler) -O3 $(test_combinations_src) -o $(binaries_directory)/$(target_test) $(compiler_flags)
	@echo "Done"

clean:
	rm -rf $(binaries_directory)
	rm -rf good_combinations

