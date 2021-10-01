awk -v var="$1" -F, 'NR == 1 { split($0, headers); next } { system("latexmk -pdflua -shell-escape -outdir=output -jobname=" $4 "_" $2 "_" $3 "_" var " " var) }' $2
find output ! -name "*.pdf" -type f -delete
