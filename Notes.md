# Notes

For general-use notes while I am going through the project.

## Setting Up the Pi

Date: 2020.11.02

<https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up/1>

Pi 4 Requires at least 3.0 Amps

At least 8GB microSD. Typically pre-installed.

Q:

* CISC Microcontrollers?
* Microcontroller - program once? Arduino is microcontroller?
* Overheating?

---

2020.11.16

## Set Up

### VSCode on Linux

* Go to [VS Code Download](https://code.visualstudio.com/download)
* Under the Penguin, we will be clicking NOT the two big buttons, but rather under those -- the ARM buttons next to `.deb`.
  * To see if you need the 32-bit or 64-bit version, type `uname -m` in the RBPi Terminal. `armv7l` or lower indicates 32-bit; `armv8` indicates 64-bit. In this case, the RBPi was `armv7l`, thus chose ARM.
* Confirm download, then click and run the file. It will install VSCode. VSCode can then be found under Programming tab of the menu.
* On the start page, has a link to setting up a Python IDE. If not, go to Extensions (the 4 squares on the left) and download "Python" and "Jupyter" Modules. If you save a `.ipynb` file, it will also suggest a Python - Get Started page

### GitHub Integration

Note: one can perfectly fine just code on the RBPi itself, in which case this GitHub stage can be skipped. As I wanted to version control my code and upload it for presentation, as well as use my custom VSCode setting on Windows, decided to set this up.

* In VSCode, on the sidebar (open by clicking the documents icon on the left), find `Clone Repository`.
* Go through the steps to log in to your GitHub, or create a GH account.
  * Note: I ran into a 801 Error Page; it still logged me in, though. If such a thing happens, go to GitHub in your browser on the Pi, log-in, copy the link of the repo, and you should be able to paste that link when you click 'Clone Repository'.

TODO: Section on creating a version control from scratch, or without GitHub.

* If sharing notebooks, must trust notebooks created on the other computer
  * I used Trust all notebooks in the settings, but this is potentially dangerous -- use with caution if you download other notebooks.
  * May need to look into running a jupyter server.
