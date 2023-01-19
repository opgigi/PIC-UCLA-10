#include "compare.h"

namespace fs = std::filesystem;

CompareFiles::CompareFiles(fs::path _user_input_directory) : root_directory(_user_input_directory) {};

// the definition of the find_all_filepath function
void CompareFiles::find_all_filepath()
{
    // runs the loops as much as the numbers of the subdirectory exist from the root directory
    for (const auto& temp_directory_address : fs::recursive_directory_iterator(root_directory))
    {
        // if temporary stored directory address is the file and not the directory then store that into the file path vector
        if (temp_directory_address.is_regular_file())
        {
            all_filepath_for_comparison.push_back(temp_directory_address);
        }
    }
}

// definition of the convert_into_singleline_txt
std::vector<char> CompareFiles::convert_into_singleline_txt(const fs::path target_file) {

    std::ifstream open_file;

    // this function opens the the file path where the tagert file is located in somewhere subdirectory.
    open_file.open(target_file);

    // if the file is not open then print out the message
    if (!open_file.is_open())
    {
        std::cout << "There was a problem opening the file.";
    }

    // this is the vector to store the whole character inforamtion while this function reading the file.
    std::vector<char> conversion_char_vector;
    char current_letter;

    // as long as the open_file can read the character from the filestream then run this loop
    while (open_file >> std::noskipws >> current_letter)
    {
        // store letter currently read from the filestream function.
        conversion_char_vector.push_back(current_letter);
    }

    open_file.close();
    open_file.clear();

    return conversion_char_vector;
}

// the deinition of creating boolean matrix from comapring those two char vectors
std::vector<std::vector<bool>> CompareFiles::matches_boolean_table(const std::vector<char>* char_vec_1, const std::vector<char>* char_vec_2)
{

    // 2d vector to store the boolean results from the comparison.
    std::vector<std::vector<bool>> boolean_table;

    // this is the char variable holds the current character that char_vec_1 holds in current index
    char current_letter = 0;

    /*
     so the point of this loop is that once the current character holds the char and then it will start to compare
     all the char values from the other char vec and compare if it overlaps or not.

     if those two char vectors share the same characters then it will store its boolean value and then hold another letter from the char vec1 and compare all the characters from the char vec2 again.

     repeating this process, they will create all the boolean table can see which character are in common between those two char vectors.
     */

     // iterate this loop as much as the size of the char_vec_1
    for (size_t i = 0; i < char_vec_1->size(); ++i)
    {

        // create an 1d vector to store all the boolean value after matching process is done.
        std::vector<bool> list_of_boolean;

        // hold one character in the current index from the char vector
        current_letter = (*char_vec_1)[i];

        // run this loop as much as the size of the char vec 2 and compare with letter from the char vec1 and store the boolean values into the bool vector.
        for (size_t j = 0; j < char_vec_2->size(); ++j)
        {

            // if the current letter that char vec1 hold are matching with any of char from the char vec 2 then store the true boolean value.
            if (current_letter == (*char_vec_2)[j])
            {
                list_of_boolean.push_back(true);
            }
            else // otherwise store that false value if the character is not matching
            {
                list_of_boolean.push_back(false);
            }

        }
        // once it finishes to store all the boolean vectors after all the char vec2 compares with single character from the char vec1, then insert that result into the boolean matrix.
        boolean_table.push_back(list_of_boolean);
    }

    // after finishing creating the boolean matrix then return the matrix.
    return boolean_table;

}


// the definition of creating match matrix
std::vector<std::vector<int>> CompareFiles::create_matching_table(const std::vector<char>* compare1, const std::vector<char>* compare2) {

    // calls the function to create the boolean matrix so can track the length of the subsequence chars
    current_boolean_table = matches_boolean_table(compare1, compare2);

    // then initialize the 2d int vector with zeros on all slots.
    std::vector<std::vector<int>> matched_table(compare1->size(), std::vector<int>(compare2->size(), 0));

    // runs this loop to filling the values on the first row and the column of the matched_table.
    for (size_t i = 0; i < compare1->size(); ++i) {
        // if the current boolean value on the first column is false then run the code inside.
        if (current_boolean_table[i][0] == false)
        {
            // if we are looking at the top left corner of the matrix then insert zero.
            if (i == 0)
            {
                matched_table[0][0] = 0;

            } // otherwise if it is located on anywhere on the first column except the top left corner then follow the upper value.
            else
            {
                matched_table[i][0] = matched_table[i - 1][0];

            }
        }
        else // otherwise if the current boolean value on the first column is true then you have to raise the number.
        {
            // if we are looking at the top left corner then raise the value by top left.
            if (i == 0)
            {
                matched_table[0][0] = 1;

            } // otherwise if it is located on anywhere on the first column except the top left corner then take the max value betwwen upper value or 1, which is the possible max.
            else
            {
                matched_table[i][0] = std::max(matched_table[i - 1][0], 1);

            }
        }
    }

    //after you initailize all the first column values on the matrix then run this loop to initailize the first row
    for (size_t j = 1; j < compare2->size(); ++j)
    {
        // if the element in the first row is false then follow the value from the previous left.
        if (current_boolean_table[0][j] == false)
        {
            matched_table[0][j] = matched_table[0][j - 1];
        }
        else // otherwise if the boolean is true then that means we have to raise the value but also need to check it can't be going over 1.
        {
            matched_table[0][j] = std::max(matched_table[0][j - 1], 1);

        }
    }

    // after we initialize all the first row and column in the matrix, then run this loop to walk through all the slots in the 2d int matrix to track the longest subsequences.
    for (size_t i = 1; i < compare1->size(); ++i)
    {
        // run this loop as much as the size of the char vector
        for (size_t j = 1; j < compare2->size(); ++j)
        {
            // once the boolean is false on the current index, shouldn't raise the value. then we have to follow the value from the previous left or top values
            if (current_boolean_table[i][j] == false)
            {
                matched_table[i][j] = std::max(matched_table[i][j - 1], matched_table[i - 1][j]);

            }
            else // otherwise if the boolean value is the true on the current index then add by one from the diagonal value.
            {
                matched_table[i][j] = 1 + matched_table[i - 1][j - 1];

            }
        }
    }

    // once this process is over, then return the match matrix.
    return matched_table;
}


// the definition of the backtracking function
void CompareFiles::backtracking(std::vector<std::vector<int>>* matched_table, const std::vector<char>* longest_word)
{
    /*
     first we need to set the the index to make it start from the bottom right corner of the matched matrix and backtracking until it comes back to the initial position.
     */
    size_t i = matched_table->size() - 1;
    size_t j = (*matched_table)[0].size() - 1;

    // this is the vector stores index to find the largest common subsequnces.
    std::vector<size_t> overlapped_index;


    // check that the index i and j are fallin within the range
    while (i > 0 && j > 0)
    {
        // if the current boolean value in the current index is true then we need to store that index to print out. and then move the index to the diagonal to prevent overcount.
        if (current_boolean_table[i][j] == true)
        {
            overlapped_index.push_back(i);

            --i;
            --j;
        }
        else if ((*matched_table)[i][j - 1] > (*matched_table)[i - 1][j]) // if the left value is larger than the upper value, then move it to the left
        {
            --j;
        }
        else // otherwise if there is no special conditions then, move it up.
        {
            --i;
        }
    }

    // checking the top left corner to see if there are empty spaces at the beginning of both char vecs.
    if ((*matched_table)[0][0] > 0)
    {
        overlapped_index.push_back(0);
    }


    // once you find all the overlapped index, but since we backtrackked from the end, then we reverse so we can see the proper overlap txt
    std::reverse(overlapped_index.begin(), overlapped_index.end());

    std::cout << "Common Subsequence Length: " << overlapped_index.size() << '\n';

    std::cout << "Overlap: \n";

    // run this loop as much as the size of overlapped characters from two files and then print out which text is overlapped.
    for (size_t temp_iterator = 0; temp_iterator < overlapped_index.size(); ++temp_iterator)
    {
        size_t z;
        z = overlapped_index[temp_iterator];
        std::cout << (*longest_word)[z];
    }


}


// the definition of getting larger vector from the comparison
const std::vector<char>* CompareFiles::vector_larger_size_comparison(const std::vector<char>* char_vec_comparison1, const std::vector<char>* char_vec_comparison2)
{
    // if the size of vec1 is larger then then the size of vec2 then return the vec1
    if (char_vec_comparison1->size() > char_vec_comparison2->size())
    {
        return char_vec_comparison1;

    } //else if the size between vec1 and vec2 are identical, then still return the vec1
    else if (char_vec_comparison1->size() == char_vec_comparison2->size())
    {
        return char_vec_comparison1;

    }
    else // otherwise, it means that the size of vec 1 is smaller than vec2 then return the vec2
    {
        return char_vec_comparison2;

    }
}

// the definition of getting smaller vector from the comparison
const std::vector<char>* CompareFiles::vector_smaller_size_comparison(const std::vector<char>* char_vec_comparison1, const std::vector<char>* char_vec_comparison2)
{
    // if the vec1 is smaller than vec2 then return the vec1
    if (char_vec_comparison1->size() < char_vec_comparison2->size())
    {
        return char_vec_comparison1;

    } // else if the vec1 size is identical with the size of the vec2 then return the vec2
    else if (char_vec_comparison1->size() == char_vec_comparison2->size())
    {
        return char_vec_comparison2;

    }
    else // otherwise, if the vec1 size is bigger than the size of vec2 then return the vec 2.
    {
        return char_vec_comparison2;

    }
}


// the definition of fiding all the possible pairwise path from all the collection of the file path stored from the find_all_filepath() function
std::vector<std::pair<fs::path, fs::path>> CompareFiles::all_possible_pairing()
{
    // call this function to collect all the file path
    find_all_filepath();

    // run this loop as much as the size of the file directory contains in the vector all_filepath_for_comparison
    for (const auto& current_file_directory : all_filepath_for_comparison)
    {
        // print out where the file locates at
        std::cout << current_file_directory << "\n";

    }

    std::vector<std::pair<std::filesystem::path, std::filesystem::path>> pair_for_comparison;


    // run this loop to
    for (size_t i = 0; i < all_filepath_for_comparison.size(); ++i)
    {
        const auto& file_directory = all_filepath_for_comparison[i];
        std::cout << file_directory << '\n';
    }

    // run this loop to store all possible pair path directory but not store the same pair twice
    for (size_t j = 0; j < all_filepath_for_comparison.size(); ++j)
    {
        /*
        if the file path 1 is set then first it will pair with file 2, 3 ,4
        but then once they are pairing the path with file 2, then they will only pair with the files from j + 1 to size of all possible file path.
        */
        for (size_t z = j + 1; z < all_filepath_for_comparison.size(); ++z)
        {
            // set the pair format and then store the path on the first and second slot.
            std::pair<fs::path, fs::path> pair_format;
            pair_format.first = all_filepath_for_comparison[j];
            pair_format.second = all_filepath_for_comparison[z];

            //insert the pairwise path into the vector
            pair_for_comparison.push_back(pair_format);

        }
    }

    return pair_for_comparison;
}

// definition of the comparison function
void CompareFiles::comparison_function() {

    // create variables vectors stores pairwise path
    std::vector<std::pair<fs::path, fs::path>> all_the_pairs;

    // then store those all possible pairwise path information into all_the_pairs
    all_the_pairs = all_possible_pairing();

    // runs the loop as much as the size of the vector, that all_the_pairs holds
    for (std::pair<fs::path, fs::path> current_pairwise_path : all_the_pairs)
    {
        // print out the format what the hw instruction wants to print:
        // Pairing [folder_name_given]/[FolderX]/[le_nameX]-[folder_name_given]/[FolderY]/[le_nameY]
        std::cout << "Pairing " << current_pairwise_path.first.string().substr(root_directory.parent_path().string().size(), current_pairwise_path.first.string().size()) << "-" << current_pairwise_path.second.string().substr(root_directory.parent_path().string().size(), current_pairwise_path.second.string().size()) << "\n";

        //after getting pairwise path, using convert_into_singleline_txt function, this will opens the file and harvest all the information to convert that into the char vector.
        const std::vector<char> string_conversion1 = convert_into_singleline_txt(current_pairwise_path.first);
        const std::vector<char> string_conversion2 = convert_into_singleline_txt(current_pairwise_path.second);

        //finds longer and shorter vectors to make sure we pass in correct ones
        const std::vector<char>* longer = vector_larger_size_comparison(&string_conversion1, &string_conversion2);
        const std::vector<char>* shorter = vector_smaller_size_comparison(&string_conversion1, &string_conversion2);

        //using create_matching_table function to create the match matrix
        std::vector<std::vector<int>> match_matrix = create_matching_table(longer, shorter);

        //using backtracking functions to track to collect all the matching element and prints out the overlap code part.
        backtracking(&match_matrix, longer);
        std::cout << "\n ----------------- \n";
    }
}
