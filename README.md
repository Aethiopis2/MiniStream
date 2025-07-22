# MiniStream

MiniStream is a real-time C++ webcam streaming demo that captures video from a webcam, encodes it to H.264 using FFmpeg, and streams it over UDP. The receiver decodes the video and displays it using OpenCV. The project is designed for Linux and leverages modern C++ with OpenCV and FFmpeg.

## ✨ Features

- Real-time webcam capture using OpenCV
- H.264 encoding with FFmpeg (libavcodec)
- Zero-copy pixel format conversion using libswscale
- UDP-based streaming for low-latency transmission
- Simple sender/receiver executables

## 📂 Project Structure

```
.
├── main_sender.cpp         # Sender executable: capture, encode, send, preview
├── main_receiver.cpp       # Receiver executable: receive, decode, display
├── capture/                # Webcam capture logic
│   ├── capture.cpp
│   └── capture.hpp
├── encode/                 # H.264 encoding logic
│   ├── encoder.cpp
│   └── encoder.hpp
├── decode/                 # H.264 decoding logic
│   ├── decoder.cpp
│   └── decoder.hpp
├── transport/              # UDP sender/receiver
│   ├── udp_sender.cpp
│   ├── udp_sender.hpp
│   ├── udp_receiver.cpp
│   └── udp_receiver.hpp
├── CMakeLists.txt
└── README.md
```

## 🏁 Usage

### Build

```bash
mkdir build && cd build
cmake ..
make
```

### Run

**Sender (on one terminal):**
```bash
./ministream_sender
```

**Receiver (on another terminal):**
```bash
./ministream_receiver
```

## ⚙️ Dependencies

- OpenCV
- FFmpeg (libavcodec, libavformat, libavutil, libswscale)
- CMake ≥ 3.10

## 🚀 How it Works

- `main_sender.cpp`: Uses [`FrameCapture`](capture/capture.hpp) to grab frames, [`FrameEncoder`](encode/encoder.hpp) to encode them, and [`UdpSender`](transport/udp_sender.hpp) to send over UDP.
- `main_receiver.cpp`: Uses [`UdpReceiver`](transport/udp_receiver.hpp) to receive packets, [`FrameDecoder`](decode/decoder.hpp) to decode, and OpenCV to display.

## 📄 License

- It's freestyle.