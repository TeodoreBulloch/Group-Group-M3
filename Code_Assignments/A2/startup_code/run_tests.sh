#!/bin/bash

# Set paths
PATH_TO_CODE_ASSIGNMENTS=~/APT_folder/APT_A2_M12/Group-Group-/Code_Assignments/A2
PATH_TO_STARTUP_CODE=${PATH_TO_CODE_ASSIGNMENTS}/startup_code
PATH_TO_TESTS=${PATH_TO_STARTUP_CODE}/TESTS_FOR_AUTOMATION

# Get the list of all input files
INPUT_FILES=$(ls ${PATH_TO_TESTS}/*.input)

# Loop over each input file
for INPUT_FILE_PATH in $INPUT_FILES
do
  # Extract the filename from the path
  INPUT_FILE=$(basename $INPUT_FILE_PATH)

  # Generate the corresponding output file name
  OUTPUT_FILE=${INPUT_FILE/.input/.actual_ppd_out}

  # Run the program and generate the output
  ./ppd ${PATH_TO_STARTUP_CODE}/stock.dat ${PATH_TO_STARTUP_CODE}/coins.dat < ${PATH_TO_TESTS}/${INPUT_FILE} > ${PATH_TO_TESTS}/${OUTPUT_FILE}

  # Compare the output to the expected output
  EXPECTED_OUTPUT=${INPUT_FILE/.input/.output}
  diff -w ${PATH_TO_TESTS}/${EXPECTED_OUTPUT} ${PATH_TO_TESTS}/${OUTPUT_FILE}
done
