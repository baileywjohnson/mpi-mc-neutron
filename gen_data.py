import csv
from subprocess import Popen, PIPE

C = 10.0
n = 1000

A = 0.01
H = 0.01
with open('data_file.csv', mode='w') as data_file:
	data_writer = csv.writer(data_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
	data_writer.writerow(['A', 'H', 'r/n', 'b/n', 't/n'])
	while A <= 0.50:
		while H <= 10:
			command = ['./nt-serial', '-C', str(C), '-A', str(round(A, 2)), '-H', str(round(H, 2)), '-n', str(n)]
			p = Popen(command, stdin=PIPE, stdout=PIPE, stderr=PIPE)
			output, err = p.communicate(b"input data")
			rc = p.returncode
			csv_format = output.split(b'\n')
			print(csv_format)
			data_writer.writerow([round(A, 2), round(H, 2), round(float(csv_format[0]), 5), round(float(csv_format[1]), 5), round(float(csv_format[2]), 5)]) #1, 2
			H += 0.01
		H = 0.01
		A += 0.01
data_file.close()
