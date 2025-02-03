
from tkinter import *
import webbrowser


def open_youtube():
    webbrowser.open_new("https://youtube.com")


# creer une premiere fenetre
window = Tk()

# personnalisé la fenetre
window.title("My application")
window.geometry("720x480")
window.minsize(480, 360)
window.iconbitmap("pt9.ico")
window.config(background="#41B77F")

# creer la frame
frame = Frame(window, bg="#41B77F")

# ajouter un premier text
label_title = Label(frame, text="Bienvenue sur mon application", font=("Courrier", 35), bg="#41B77F", fg="white")
label_title.pack()

# ajouter un second text
label_subtitle = Label(frame, text="Hello World", font=("Courrier", 25), bg="#41B77F", fg="white")
label_subtitle.pack()

# ajouter un premier bouton
yt_button = Button(frame, text="Ouvrir youtube", font=("Courrier", 25), bg="white", fg="#41B77F", command=open_youtube)
yt_button.pack(pady=25, fill=X)

# afficher la frame
frame.pack(expand=YES)

# afficher la fenetre
window.mainloop()
