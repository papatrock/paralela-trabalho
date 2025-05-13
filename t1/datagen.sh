#!/bin/bash

THREADS_NUMBERS=(1 2 4 8 16)
INPUT_DIR="entradas"
OUTPUT_DIR="saidas"
INPUTS="size100 size1k size10k size20k size40k"

OUTPUT_FILE="${OUTPUT_DIR}/saida.out"
mkdir -p "${OUTPUT_DIR}"

echo -n "N         |" > "$OUTPUT_FILE"
for input in $INPUTS; do
  size_label=$(echo "$input" | sed 's/size//')
  printf " %-10s |" "$size_label" >> "$OUTPUT_FILE"
done
echo "" >> "$OUTPUT_FILE"

echo "----------------------------------------------------------------------------" >> "$OUTPUT_FILE"

for((i=0; i < 20; i++));do
echo -n "Sequencial|" >> "$OUTPUT_FILE"

  for input in $INPUTS; do
    tempo=$(./lcs "${INPUT_DIR}/${input}A.in" "${INPUT_DIR}/${input}B.in")
    printf " %-8s |" "$tempo" >> "$OUTPUT_FILE"
  done
  echo "" >> "$OUTPUT_FILE"

  for t in "${THREADS_NUMBERS[@]}"; do
    printf "%-10s|" "${t} CPU" >> "$OUTPUT_FILE"
    for input in $INPUTS; do
      tempo=$(./lcs-para "${INPUT_DIR}/${input}A.in" "${INPUT_DIR}/${input}B.in" $t)
      printf " %-8s |" "$tempo" >> "$OUTPUT_FILE"
    done
    echo "" >> "$OUTPUT_FILE"
  done

done
