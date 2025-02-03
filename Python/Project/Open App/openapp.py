import os
import difflib

roots = ["C:\\", "D:\\"] # Liste des disques durs à explorer

all_files = []
for root in roots:
    for dirpath, dirnames, filenames in os.walk(root):
        for filename in filenames:
            if filename.endswith(".exe"):
                all_files.append(os.path.join(dirpath, filename))

def find_app(app_name):
    matches = difflib.get_close_matches(app_name, [os.path.basename(file) for file in all_files])
    if matches:
        return matches[0]
    else:
        return None

while 1 > 0:
    app_input = input("Entrez le nom de l'application : ")
    app_file = find_app(app_input)

    if app_file:
        for root in roots:
            for dirpath, dirnames, filenames in os.walk(root):
                if app_file in filenames:
                    os.startfile(os.path.join(dirpath, app_file))
                    break
    else:
        print("Application non trouvée.")
