
import glob, os
from tqdm import tqdm

path = ""
exts = "c cpp h".split(" ")

all_files = []
for file in glob.glob(os.path.abspath(path) + r"\**\*.*", recursive=True):
	if not file.lower().split(".")[-1] in exts: continue
	all_files.append(file)

# file stats
pbar = tqdm(total=len(all_files))
lines, chars = 0, 0
for file in all_files:
	# print(file)
	pbar.update(1)
	chars += os.path.getsize(file)
	try:
		with open(file, "r") as fobj:
			lines += len(fobj.readlines())
	except:
		pass
pbar.close()

print()
print("Anzahl Dateien: " + str(len(all_files)))
print("Gesamt Größe: " + str(chars) + " Bytes")
print("Anzahl Code-Zeilen: " + str(lines))
input()
