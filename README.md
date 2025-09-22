# VoxExMachina


⸻


# 🎭 Vox Ex Machina: Gala Edition

**Vox Ex Machina** is an interactive audiovisual installation and live performance interface designed to transform operatic vocals into expressive visual and sonic representations. This **Gala Edition** was built specifically for Opera Philadelphia’s 50th Anniversary Gala.

It functions as both a performance tool and a visualization engine, combining pitch detection, amplitude mapping, and dynamic graphics to give form to the ephemeral nature of voice.

---

## 🧭 Interface Sections & Controls

### 🎤 **Mic Channel Selector**
- Toggle between five mic sources:
  - Marina
  - Stephanie
  - Will
  - Anthony
  - Daniela
- Modes: `Off`, `Player`, `Live`

### 🧠 **Analysis & Control**
- **Pitch Detection**: Detects and displays pitch in real time, using a piano roll.
- **Amplitude Compression**: Adjustable AMP COMP knob.
- **Pitch Compression**: Manual slider to smooth pitch jumps.
- **Song Range**: Defines low/high note range and tracks current detected pitch.

### 🎚 **Sliders and Presets**
- Compressor Renaissance Vox for Amplitude and Pitch
- Preset selector with five vocalists
- Custom artwork-based preset buttons
- Serial Port control: `print`, `open`, `close`, `clear`

### ⏱ **Playback & Mapping**
- Song Length setting (in minutes and seconds)
- Time to end
- Elapsed time counter
- Number of lines
- Time per line calculated from total duration

### 🎛 **Aria Controls**
- Five aria buttons (`Aria #1` to `Aria #5`)
- Manual mode toggle for mapped output box
- Graphic display window for mapping/animation

---

## 🚀 How to Run

1. Open `VoxExMachina_GALA.maxproj` in Max/MSP (v8+ recommended).
2. Ensure `code/` and `data/` folders are in the project directory.
3. Follow the **startup instructions**:

	1.	Print port and select it
	2.	Select audio interface and start audio
	3.	Select Player or Live mode
	4.	RESET

---

## 🔁 When Each Aria Ends

	1.	SW: Click on STOP
	2.	HW: Lift the head
	3.	SW: RESET
	4.	HW: Turn off machine outlet
	5.	HW: Jake and Burak reset machine manually
	6.	HW: Turn machine back on
	7.	HW: Remove acrylic
	8.	HW: Put new acrylic
	9.	SW: Change preset
	10.	SW: Lower the head
	11.	AUDIO: Change channel switch on arias 2 and 4

---

## 🧠 Features

- 🎤 Real-time pitch and amplitude analysis
- 🎨 Voice-driven visualization in XY space
- 🧩 Performer-specific preset selection
- 🧵 Live interaction with hardware (via serial)
- 📊 Visual countdown & timing feedback
- 🎚 Automated mapping across time + space
- 🧰 Flexible input switching and modular routing

---

## 🧑‍🎨 Credits

- **Daniel Belquer** – Creative Lead, Max/MSP development
- **Daniel Belquer, Cole Seidel and Luke Hathaway** - Max patch
- **Luke Hathaway and Jacob Zolda** - Firmware
- **Jacob Zolda** - Electronics
- **Burak Demirelli** - Mechanical engineering
- **David Lu** - General technical help
- **Youngmoo Kim** – Academic Advisor
- **Anthony Roth Costanzo** – Vocal Performer
- **ExCITe Center, Lenfest Center, Drexel University** – Technical & institutional partner
- **Opera Philadelphia** – Production Partner

---

## 📜 License

MIT License.

---

## 🐛 Issues

Feel free to open an issue if you encounter bugs or have suggestions.

---
