# Alien Force — Earth vs. Alien Army Simulation

A C++ simulation of a war between an Earth army and an invading alien army, built for a Data Structures course. Each unit type lives in a data structure chosen for how that unit fights, and the simulation reports per-unit timings and army-wide statistics.

## How it works

Every time step:

1. A random generator decides, with probability `Prob`, whether to add `N` new units to each army. The unit mix, power, health and attack capacity are drawn from the ranges in the scenario file.
2. The Earth army attacks, then the alien army attacks. Units whose health reaches zero move to a killed list.
3. From step 40 on, the game ends as soon as an army is wiped out. The result is recorded from Earth's side as Win, Loss or Draw. If the user's step limit comes first, the army with more units left wins.

## Units and data structures

| Army | Unit | Data structure | Why |
|---|---|---|---|
| Earth | Soldier | `LinkedQueue` | Soldiers fight in arrival order (FIFO) |
| Earth | Tank | `ArrayStack` | The most recently added tank fights first (LIFO) |
| Earth | Gunnery | `priQueue` | The strongest gunnery attacks first; priority = power × health / 100 |
| Alien | Soldier | `LinkedQueue` | FIFO, like Earth soldiers |
| Alien | Drone | `Dequeue` | Two drones attack each step, one from the front and one from the back |
| Alien | Monster | `MonsterArray` | A random monster is picked each step, which needs O(1) random access |

All containers are implemented from scratch. `ArrayStack` and `LinkedQueue` implement the `StackADT`/`QueueADT` interfaces, `priQueue` is a sorted linked list, `Dequeue` extends `LinkedQueue` with back access, and `MonsterArray` is a fixed array with random removal.

## Running

On start, the program asks for:

1. **A scenario:** weak, moderate or strong aliens against a weak or strong Earth, giving six input files such as `StrongEarth_ModerateAliens.txt`.
2. **A mode:** *silent* runs to the end and only writes the output file. *Interactive* prints every step: the attacking units, the units they hit, and each army's lists.
3. **A time-step limit** of at least 40.

Build with Visual Studio (`Alien Force phase1.sln`), or with g++ from `Alien Force phase1/`:

```bash
g++ -std=c++17 -include cmath -o alienforce *.cpp   # -include cmath: MSVC pulls <cmath> in implicitly
./alienforce
```

## Input file format

```text
5              # N: units generated per army each time the generator fires
10 20 70       # Earth mix (%): soldiers, tanks, gunnery
50 20 30       # Alien mix (%): soldiers, monsters, drones
70             # Prob (%): chance the generator fires in a given step
300-500 80-90 5-8     # Earth ranges: power, health, attack capacity
200-300 60-80 5-8     # Alien ranges: power, health, attack capacity
```

## Output

Each scenario writes `<Scenario>_output.txt`, and the six committed `_output.txt` files are sample runs. The file lists every destroyed unit in order of destruction:

| Column | Meaning |
|---|---|
| `Td` | Time step the unit was destroyed |
| `ID` | Unit ID (Earth units count up from 1, alien units from 2000) |
| `Tj` | Time step the unit joined |
| `Df` | First-shot delay: first attacked − joined |
| `Dd` | Destruction delay: destroyed − first attacked |
| `Db` | Battle time: `Df + Dd` |

After the table come the battle result and, for each army, totals per unit type, the percentage of each type destroyed, and average `Df`, `Dd` and `Db`.
