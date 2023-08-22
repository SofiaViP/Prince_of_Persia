## 2. Project Status

### 2.1. IO devices Used

| Device     | Use                                       | Interrupts |
|------------|-------------------------------------------|------------|
| Timer      | Set frame rate and time count             | Yes        |
| KBD        | Character movement and menu navigation    | Yes        |
| Mouse      | Hit the targets                           | Yes        |
| Video Card | Menus, characters and objects display     | No         |
| RTC        | In game time and scoreboard date and time | Yes        |

### 2.2. Timer

The timer in our game serves multiple essential purposes. Firstly, it is responsible for setting the frame rate, ensuring smooth and consistent visuals during the gameplay. This ensures that the game's graphics and animations are displayed at a controlled and optimal speed.

The timer also plays a crucial role in shrinking the elusive and challenging targets in our game. As time progresses, the timer triggers events that gradually reduce the presence of these targets, increasing the difficulty and excitement for the players.


To configure the timer we subscribe the interrupts 
(**timer_subscribe_int(uint8_t\* bit_no)**), this way our program receives notifications whenever a timer event occurs. The **sys_hz()** system call provides us with the frequency of the system's timer interrupts, allowing us to accurately detect the passage of time. With this information, we can precisely track the timing and synchronization of various game events.

The **timer_int_handler()** function is responsible for handling the events triggered by the timer interrupts, therefore ensures that all the above features occur smoothly.

### 2.3. Keyboard

The keyboard holds a crucial role in our project as it serves not only to control the movement of the prince but also to navigate through the interface, making it a vital component of the overall user experience.

To configure the keyboard in our project, we subscribe to keyboard interrupts using the function (**keyboard_subscribe_int(uint8_t\* bit_no)**). This subscription ensures that our program receives notifications whenever a keyboard event occurs, allowing us to respond accordingly.

Upon receiving a keyboard interrupt, the program obtains a \textbf{scancode}, which is a unique code associated with the key pressed by the user. This \textbf{scancode} plays a pivotal role in determining the subsequent action to be taken within the project. First, it is processed by the keyboard interrupt handler, **kbd_ih()**, which then delegates the work of moving the Prince to the **change_prince_state(uint8_t scancode)** function.

### 2.4. Mouse

The mouse serves a significant role during the final battle of the game, although it remains visible throughout the entire gameplay.

To configure the mouse we start by enabling the data reporting (**mouse_enable_data_report()**), allowing the mouse to transmit information. Subsequently, we subscribe the mouse interrupts (**mouse_subscribe_int(uint_8\* bit_no)**), ensuring that our program receives notifications whenever a mouse event occurs.

When a mouse interrupt is triggered, it transmits a packet consisting of three bytes. These bytes contain essential information that we parse and interpret. This information includes the cursor movement and any buttons that are being clicked by the user. In the **mouse_ih()** function, we parse these packets and, with the help of **parse_movement(struct packet pp)** and  **change_mouse_state()** functions we are able to detect both hits and misses on the targets in the Fight Screen.

### 2.5. Graphics Card

The Graphics Card is very important for our project, since it is used to display the menus, the characters, the objects and the text.

To configure the graphics card we call our **vg_init(uint16_t mode)** function with mode 0x115:

| Mode  | Screen Resolution | Color Model  | Bits per pixel (R:G:B) | Number of Colors |
|-------|-------------------|--------------|------------------------|------------------|
| 0x115 | 800x600           | Direct Color | 24 (8:8:8)             | 16 777 216*      |

**Note:** *Number of colors = $2^8 \times 2^8 \times 2^8$

We decided to implement **triple buffering** via copy, as a mean to provide the animations found in every menu, using the **swap_buffers(bool buffer)** function. You can find more information about this, in the [Triple Buffering](Implementation.md#Triple_Buffering) subsection.

As mentioned before, we take advantage of the Video Card to animate our prince, targets and cursor. For this, we make use of the combination of **draw_xpm(xpm_image img, uint16_t x, uint16_t y, bool buffer)** and **erase_xpm(xpm_image img, uint16_t x, uint16_t y, bool buffer)**.

The Video Card is also useful for the collision detection part of our project (**check_collision(position_t
pos1, position_t pos2)**), since it would be unfortunate if the prince went straight through the walls.

### 2.6. Real Time Clock

The RTC is used for both the in-game timer and for adding a date-time stamp to the Scoreboard. This device is configured using the update interrupt since we need interrupts to happen every second (**rtc_set_interrupts()**). 

Whenever an RTC interrupt occurs the current date-time is updated to it’s new value (**rtc_update()**). When in game, an RTC interrupt will also update the chronometer,  **increase_timer()**, in the top-right corner of the screen. 

Interrupt decisions are all made by the **rtc_ih()** function.