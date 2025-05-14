#!/bin/bash

THREADS_NUMBERS=(1 2 4 8 16)
INPUT_DIR="entradas"
OUTPUT_DIR="saidas"
INPUTS="size100 size1k"

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

# média e desvio padrão
echo -e "\n\nMÉDIAS e DESVIO PADRÃO:" >> "$OUTPUT_FILE"
echo -n "N         |" >> "$OUTPUT_FILE"
for input in $INPUTS; do
  size_label=$(echo "$input" | sed 's/size//')
  printf "             %-27s |" "$size_label" >> "$OUTPUT_FILE"
done
echo "" >> "$OUTPUT_FILE"

echo "----------------------------------------------------------------------------" >> "$OUTPUT_FILE"


awk -F'\\|' '
{
  gsub(/^[ \t]+|[ \t]+$/, "", $1);  # limpa espaços do tipo (coluna 1)
}

$1 ~ /^Sequencial$|^[0-9]+ CPU$/ {
  tipo = $1
  for (i = 2; i <= NF; i++) {
    gsub(/^[ \t]+|[ \t]+$/, "", $i);  # limpa espaços do campo numérico
    if ($i != "") {
      valor = $i + 0  # força número
      sum[tipo, i] += valor
      count[tipo, i] += 1
      sum_sq[tipo, i] += valor * valor  # Soma dos quadrados dos valores
    }
  }
  tipos[tipo] = 1
  max_col = (NF > max_col ? NF : max_col)
}

END {
  for (tipo in tipos) {
    printf "%-11s|", tipo
    for (i = 2; i <= max_col; i++) {
      if (count[tipo, i] > 0) {
        mean = sum[tipo, i] / count[tipo, i]
        variance = (sum_sq[tipo, i] / count[tipo, i]) - (mean * mean)
        stddev = sqrt(variance)
        printf " Média: %.8f | Desvio: %.8f |", mean, stddev
      } else {
        printf "    -     |    -     |"
      }
    }
    print ""
  }
}
' "$OUTPUT_FILE" >> "$OUTPUT_FILE"