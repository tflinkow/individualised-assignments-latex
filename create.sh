# parameters:
#                $1       $2
# ./create.sh document list.csv
#             ^^^^^^^^
#             tex file ^^^^^^^^
#                      csv file

mkdir -p output

{
  # skip the first line containing the headers
  read
  
  # csv file: [[id]],Vorname,Nachname,Matrikelnummer,Institution,Abteilung,E-Mail-Adresse,gesperrt,"Zuletzt aus diesem Kurs geladen"
  while IFS="," read -r id firstname lastname matriculationnumber unused1 unused2 unused3 unused4 unused5
  do
    # turn "A Super Long Name" into "A-Super-Long-Name"
    firstname="${firstname// /-}"
    
    # remove possible prefix and suffix " characters
    firstname="${firstname%\"}"
    firstname="${firstname#\"}"
    
    # turn "A Super Long Name" into "A-Super-Long-Name"
    lastname="${lastname// /-}"
    
    # remove possible prefix and suffix " characters
    lastname="${lastname%\"}"
    lastname="${lastname#\"}"
  
    # the name of the PDF file without solutions
    jobname="${matriculationnumber}_${firstname}_${lastname}"
    
    # the name of the PDF file with solutions
    jobnamewithsolution="${matriculationnumber}_${firstname}_${lastname}_Solution"
    
    echo $jobname

    # compile each file twice to account for total points calculation etc.
    #for i in { 1..2 };
    #do
      lualatex --shell-escape --interaction=batchmode -output-directory=output -jobname=$jobname $1 $matriculationnumber $firstname $lastname
      lualatex --shell-escape --interaction=batchmode -output-directory=output -jobname=$jobname $1 $matriculationnumber $firstname $lastname
    
      lualatex --shell-escape --interaction=batchmode -output-directory=output -jobname=$jobnamewithsolution $1 $matriculationnumber $firstname $lastname answers
      lualatex --shell-escape --interaction=batchmode -output-directory=output -jobname=$jobnamewithsolution $1 $matriculationnumber $firstname $lastname answers
    #done
  done
} < $2 

# delete auxiliary files and logs
find output ! -name "*.pdf" -type f -delete
