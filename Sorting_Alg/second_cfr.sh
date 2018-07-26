#estrae da ogni modo una lista
#!/bin/bash
for k in 1 2 3 4 5; do
  cat ./dataset/log.dat | grep M:${k} | gawk -v FS="," '{ print $2}' > ./dataset/step_log/mode${k}.step
  cat ./dataset/log.dat | grep M:${k} | gawk -v FS="," '{ print $3}' > ./dataset/time_log/mode${k}.time
done

./exe/histogram.exe ./dataset/step_log/mode1.step 50 ./dataset/step_log/histograms/h_mode1.dat
./exe/histogram.exe ./dataset/step_log/mode2.step 50 ./dataset/step_log/histograms/h_mode2.dat
./exe/histogram.exe ./dataset/step_log/mode3.step 50 ./dataset/step_log/histograms/h_mode3.dat
./exe/histogram.exe ./dataset/step_log/mode4.step 50 ./dataset/step_log/histograms/h_mode4.dat
./exe/histogram.exe ./dataset/step_log/mode5.step 50 ./dataset/step_log/histograms/h_mode5.dat

./exe/histogram.exe ./dataset/time_log/mode1.time 50 ./dataset/time_log/histograms/h_mode1.dat
./exe/histogram.exe ./dataset/time_log/mode2.time 50 ./dataset/time_log/histograms/h_mode2.dat
./exe/histogram.exe ./dataset/time_log/mode3.time 50 ./dataset/time_log/histograms/h_mode3.dat
./exe/histogram.exe ./dataset/time_log/mode4.time 50 ./dataset/time_log/histograms/h_mode4.dat
./exe/histogram.exe ./dataset/time_log/mode5.time 50 ./dataset/time_log/histograms/h_mode5.dat
