echo "Today date is `date`"
cal > menuchoice.temp.$$
dialog --backtitle "Linux Shell Tutorial" --title "Calender" --infobox "`cat menuchoice.temp.$$`" 9 25 ; read

