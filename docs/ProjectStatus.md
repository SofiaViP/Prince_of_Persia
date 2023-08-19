## 2. Project Status

### 2.1. IO devices Used

| Device     | Use                                       | Interrupts |
|------------|-------------------------------------------|------------|
| Timer      | Set frame rate and time count             | Yes        |
| KBD        | Character movement and menu navigation    | Yes        |
| Mouse      | Hit the targets                           | Yes        |
| Video Card | Menus, characters and objects display     | No         |
| RTC        | In game time and scoreboard date and time | Yes        |

### 2.2 Timer

The timer in our game serves multiple essential purposes. Firstly, it is responsible for setting the frame rate, ensuring smooth and consistent visuals during the gameplay. This ensures that the game's graphics and animations are displayed at a controlled and optimal speed.

The timer also plays a crucial role in shrinking the elusive and challenging targets in our game. As time progresses, the timer triggers events that gradually reduce the presence of these targets, increasing the difficulty and excitement for the players.


To configure the timer we subscribe the interrupts 
(**timer_subscribe_int(uint8_t\* bit_no)**), this way our program receives notifications whenever a timer event occurs. The **sys_hz()** system call provides us with the frequency of the system's timer interrupts, allowing us to accurately detect the passage of time. With this information, we can precisely track the timing and synchronization of various game events.

The **timer_int_handler()** function is responsible for handling the events triggered by the timer interrupts, therefore ensures that all the above features occur smoothly.