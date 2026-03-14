# QUANTUM AGENT TARS - USER MANUAL
### Complete Guide for End Users

<div align="center">

| Document Version | Software Version | Date | Author |
|------------------|------------------|------|--------|
| 1.0 | 0.1.0 | March 14, 2026 | Dan Fernandez |

</div>

---

## TABLE OF CONTENTS
1. [Introduction](#introduction)
2. [System Requirements](#system-requirements)
3. [Installation Guide](#installation-guide)
4. [Running the System](#running-the-system)
5. [Using the Software](#using-the-software)
6. [Troubleshooting](#troubleshooting)
7. [Frequently Asked Questions](#frequently-asked-questions)
8. [Contact Support](#contact-support)

---

## INTRODUCTION

Quantum Agent TARS is a software framework that runs AI agents on your computer. It can:

- Run 333 AI agents simultaneously
- Secure communications with post-quantum encryption
- Monitor system health and performance
- Validate that no one has tampered with the software

**This guide will teach you how to install and use it, even if you have never used command line before.**

---

## SYSTEM REQUIREMENTS

### Minimum Requirements
- **Operating System:** Windows 10/11, Ubuntu 22.04, or macOS 13+
- **CPU:** 4 cores @ 2.0 GHz
- **RAM:** 4 GB
- **Storage:** 10 GB free space
- **Internet:** Required for installation

### Recommended Requirements
- **CPU:** 8 cores @ 3.0 GHz
- **RAM:** 16 GB
- **Storage:** 50 GB SSD
- **Internet:** 100 Mbps

---

## INSTALLATION GUIDE

### Method 1: Docker (Easiest - 5 minutes)

#### Step 1: Install Docker

**For Windows:**
1. Go to https://www.docker.com/products/docker-desktop/
2. Download Docker Desktop
3. Run the installer
4. Restart your computer
5. Open Docker Desktop (search in Start menu)

**For Ubuntu:**
```bash
sudo apt update
sudo apt install docker.io
sudo usermod -aG docker $USER
newgrp docker
```

**For macOS:**
```bash
brew install --cask docker
# Or download from docker.com
```

#### Step 2: Pull the Docker Image
Open a terminal (Command Prompt on Windows, Terminal on Mac/Linux) and type:

```bash
docker pull ghcr.io/primordialomegazero/quantum-agent-tars/app:latest
```

Wait for the download to finish. It's about 900MB.

#### Step 3: Run the Container
```bash
docker run -p 4724:4724 -p 8080:8080 -p 33000:33000 ghcr.io/primordialomegazero/quantum-agent-tars/app:latest
```

You should see:
```
========================================
QUANTUM AGENT TARS v0.1.0
Source: DanFernandezIsTheSourceinHumanForm
========================================
Embedding watermark...
✓ All modules validated
System running... (heartbeat 100)
```

**The system is now running.**

---

### Method 2: Build from Source (For Advanced Users)

#### Step 1: Install Prerequisites

**For Ubuntu:**
```bash
sudo apt update
sudo apt install -y build-essential cmake git libssl-dev
```

**For Windows:**
1. Install WSL 2 (Windows Subsystem for Linux)
2. Open PowerShell as Administrator
3. Type: `wsl --install`
4. Restart
5. Open Ubuntu from Start menu
6. Run the Ubuntu commands above

**For macOS:**
```bash
xcode-select --install
brew install cmake git openssl
```

#### Step 2: Download the Source Code
```bash
git clone https://github.com/primordialomegazero/quantum-agent-tars.git
cd quantum-agent-tars
```

#### Step 3: Build the Software
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

Wait for compilation to finish. This takes 2-5 minutes.

#### Step 4: Run the Software
```bash
./quantum_agent_tars
```

---

## RUNNING THE SYSTEM

### Starting the System

Once installed, the system runs continuously until you stop it.

**Expected output when running:**
```
========================================
QUANTUM AGENT TARS v0.1.0
Source: DanFernandezIsTheSourceinHumanForm
========================================

Embedding watermark...
✓ All modules validated
System running... (heartbeat 100)
System running... (heartbeat 200)
System running... (heartbeat 300)
```

The heartbeat message appears every 10 seconds to show it's working.

### Stopping the System

Press **Ctrl + C** in the terminal where the system is running.

You should see:
```
^C
```

The system stops gracefully.

### Restarting the System

If using Docker:
```bash
docker run -p 4724:4724 -p 8080:8080 -p 33000:33000 ghcr.io/primordialomegazero/quantum-agent-tars/app:latest
```

If built from source:
```bash
cd ~/quantum-agent-tars/build
./quantum_agent_tars
```

---

## USING THE SOFTWARE

### Accessing the Web Interface

Once the system is running, open your web browser and go to:

```
http://localhost:8080
```

You will see the Swagger UI interface. This is where you can:
- See all available API endpoints
- Test commands directly
- View system status

### Checking System Health

Open a new terminal and type:
```bash
curl http://localhost:33000/health
```

Expected response:
```json
{"status":"healthy","uptime":3600}
```

The uptime is in seconds.

### Viewing Performance Metrics

```bash
curl http://localhost:33000/metrics
```

You will see output like:
```
# HELP appium_uptime_seconds Uptime in seconds
# TYPE appium_uptime_seconds counter
appium_uptime_seconds 3600

# HELP appium_memory_usage_mb Memory usage in MB
# TYPE appium_memory_usage_mb gauge
appium_memory_usage_mb 128
```

### Testing the Main Server

```bash
curl http://localhost:4724/
```

Expected response:
```json
{
  "status": "ok",
  "source": "DanFernandezIsTheSourceinHumanForm",
  "threads": 4
}
```

### Running the 333 Agents

The agents run automatically. You don't need to do anything. They are:
- NanoAgent: Individual processing units
- AgentSwarm: Coordinates all agents
- RecursiveOrchestrator: Optimizes agent distribution

### Using Post-Quantum Security

The system automatically uses post-quantum encryption for all communications. You don't need to configure anything. The following algorithms are active:

- CRYSTALS-Kyber-1024 (key exchange)
- CRYSTALS-Dilithium-5 (signatures)
- FALCON (compact signatures)
- SPHINCS+ (stateless signatures)

---

## TROUBLESHOOTING

### Problem: "docker: command not found"

**Solution:** Docker is not installed. Install Docker Desktop from docker.com or use:
```bash
sudo apt install docker.io
```

### Problem: "port already in use"

**Solution:** Another program is using the port. Find and stop it:
```bash
# On Ubuntu/Mac
sudo lsof -i :4724
kill -9 <PID>

# On Windows (PowerShell as Admin)
netstat -ano | findstr :4724
taskkill /PID <PID> /F
```

### Problem: System hangs at "Embedding watermark..."

**Solution:** The watermark validation is taking too long. Check if source files exist:
```bash
ls -la src/
```

If files are missing, re-clone the repository.

### Problem: "✓ All modules validated" never appears

**Solution:** The system may be stuck. Press Ctrl+C and restart. If problem persists, disable watermark temporarily:
1. Open `src/main.cpp`
2. Comment out the watermark section
3. Rebuild

### Problem: Heartbeat messages stop appearing

**Solution:** The system may have crashed. Check if process is running:
```bash
ps aux | grep quantum_agent_tars
```

If not running, restart.

### Problem: Docker image pull fails

**Solution:** Check internet connection and login:
```bash
docker login ghcr.io -u primordialomegazero
# Use token as password
```

---

## FREQUENTLY ASKED QUESTIONS

### Q: Do I need to be a programmer to use this?

**A:** No. If you use Docker, you only need to copy-paste 3 commands. If you can use a terminal, you can run this software.

### Q: What is the God Watermark?

**A:** It's a protection mechanism that checks if anyone modified the source code. If the code is changed, the system detects it and refuses to run.

### Q: How do I know it's working?

**A:** You will see "System running... (heartbeat 100)" messages every 10 seconds. You can also check the web interface at http://localhost:8080

### Q: Can I run this on a server?

**A:** Yes. Use Docker and expose the ports. Make sure to configure firewall rules appropriately.

### Q: How much does it cost?

**A:** It's free and open source under MIT license.

### Q: Is it safe to run?

**A:** Yes. It runs in user space and does not require root/admin privileges. The Docker container is isolated from your system.

### Q: What if I find a bug?

**A:** Contact the developer at danfernandez9292@gmail.com

### Q: Can I modify the code?

**A:** Yes, it's open source. But if you modify it, the God Watermark validation will fail. You can disable it by editing `src/god/watermark.h` and adding `#define WATERMARK_DISABLED`.

### Q: How do I update to a new version?

**A:** If using Docker:
```bash
docker pull ghcr.io/primordialomegazero/quantum-agent-tars/app:latest
```

If from source:
```bash
cd quantum-agent-tars
git pull
rm -rf build
mkdir build && cd build
cmake ..
make
```

### Q: The system uses 25% of my RAM. Can I change this?

**A:** Yes. Edit `src/system/MemoryLimiter.cpp` and change the `max_percent_` value. Rebuild after changing.

---

## CONTACT SUPPORT

If you encounter issues not covered in this manual, contact:

**Developer:** Dan Fernandez

| Method | Contact |
|--------|---------|
| Primary Email | danfernandez9292@gmail.com |
| Secondary Email | devilswithin13@gmail.com |
| GitHub Issues | https://github.com/primordialomegazero/quantum-agent-tars/issues |
| Messenger | facebook.com/sarapmagsleep |

**When reporting issues, please include:**
- Your operating system
- Installation method (Docker or source)
- Error messages (copy-paste the exact text)
- Steps you took before the error

---

## GLOSSARY

| Term | Definition |
|------|------------|
| Agent | A small AI processing unit |
| Docker | A container platform that packages software |
| Endpoint | A specific URL where you can interact with the system |
| Heartbeat | A periodic signal showing the system is alive |
| Port | A numbered channel for network communication |
| Post-Quantum | Cryptography designed to resist quantum computers |
| Swagger | A tool that provides interactive API documentation |
| Watermark | A validation mechanism that checks code integrity |

---

<div align="center">
**END OF USER MANUAL**

[GitHub Repository](https://github.com/primordialomegazero/quantum-agent-tars) | [Docker Images](https://ghcr.io/primordialomegazero/quantum-agent-tars/app:latest)
</div>