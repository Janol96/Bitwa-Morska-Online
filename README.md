# 🚢 Bitwa Morska Online

**Bitwa Morska Online** to klasyczna gra w statki stworzona w języku **C++** z wykorzystaniem biblioteki **SFML**. Projekt umożliwia rozgrywkę jednoosobową z przeciwnikiem AI oraz (wstępnie) tryb sieciowy LAN. Gra oferuje ręczne rozmieszczanie statków, intuicyjny interfejs i oprawę graficzną opartą o modele `.png`.

> 🎓 Projekt zrealizowany jako zaliczenie na studiach Automatyki i Robotyki (Politechnika Poznańska).

---

## 🎮 Funkcje gry

- ✅ Tryb jednoosobowy z przeciwnikiem AI
- 🧪 Tryb wieloosobowy LAN (wersja testowa, wymaga dopracowania)
- 🧊 Ghost-mode: podgląd statku przed rozmieszczeniem
- 🔁 Naprzemienne tury, oznaczanie trafień i pudeł
- 🏁 Ekran końcowy: WYGRANA / PRZEGRANA
- 🖼️ Grafika oparta o pliki `.png` (statki, tło, trafienia)

---

## ⚙️ Wymagania

- System operacyjny: Windows / Linux / macOS
- Kompilator C++ z obsługą standardu C++17
- **[SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/)**
- Qt Creator (projekt używa `qmake`)

---

## 🛠️ Kompilacja i uruchomienie

1. **Zainstaluj bibliotekę SFML 2.5.1**
   - Na Windows najlepiej użyć wersji kompatybilnej z MinGW
   - Na Linuxie: `sudo apt install libsfml-dev`

2. **Sklonuj repozytorium**
   ```bash
   git clone https://github.com/Janol96/Bitwa-Morska-Online.git
   cd Bitwa-Morska-Online
3. Otwórz projekt w Qt Creator i zbuduj go przez qmake

4. PRZED URUCHOMIENIEM:
Skopiuj zawartość folderu assets/ do katalogu build/[nazwa]

---

## 🧠 Struktura projektu
main.cpp – menu główne, uruchamianie gry
Game.* – zarządzanie turami, zakończeniem, graczem i AI
NetworkManager.* – połączenie klient-serwer w LAN (do dopracowania)
Board, Player, Ship – klasy reprezentujące logikę planszy
assets/ – folder z grafikami i czcionkami (.png) wymagany do uruchomienia

---

## 🚧 Znane problemy / Do dopracowania
🔌 Tryb LAN nie jest jeszcze w pełni funkcjonalny

---

## 💡 Planowane ulepszenia
🎵 Dodanie dźwięków i muzyki

📝 Informacje kontekstowe podczas gry (np. tura, status)

🧑‍🤝‍🧑 Usprawnienie trybu LAN i pełna synchronizacja statków

🎨 Ustawienia grafiki: wybór tła, modeli statków

🔊 Ustawienia dźwięku

---

## 👨‍💻 Autorzy
Zespół projektowy – studenci AiR, Politechnika Poznańska:

Jan Handke
Jakub Jastrząb

---

## 📄 Licencja
Projekt edukacyjny. Wszelkie prawa zastrzeżone © 2025.
