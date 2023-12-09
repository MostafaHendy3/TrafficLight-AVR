#!/bin/bash

echo "Enter Module Name"
read ModuleName
touch ${ModuleName}_prog.c
touch ${ModuleName}_Int.h
touch ${ModuleName}_priv.h
touch ${ModuleName}_config.h
echo "Done Creating Files"

# Directory containing header files (change this to your directory)
header_dir="."

# Search for header files and loop through them
find "$header_dir" -type f -name "*.h" -print0 | while IFS= read -r -d $'\0' header_file; do
    # Get the filename without the path
    filename=$(basename "$header_file")

    # Extract the file extension (without the dot)
    file_extension="${filename##*.}"

    # Extract the filename without the extension
    file_name="${filename%.*}"

    # Create the include guard name by converting the filename to uppercase
    include_guard="${file_name^^}_${file_extension^^}_"

    # Create a temporary file with the updated content
    tmp_file=$(mktemp)

    # Add the file guard to the temporary file
    echo "#ifndef $include_guard" >> "$tmp_file"
    echo "#define $include_guard" >> "$tmp_file"

    # Append the original content of the header file
    cat "$header_file" >> "$tmp_file"

    # Add the file guard closing statements
    echo "#endif /* $include_guard */" >> "$tmp_file"

    # Replace the original header file with the temporary file
    mv "$tmp_file" "$header_file"

    echo "File guard added to: $header_file"
done

echo "File guard addition completed."
