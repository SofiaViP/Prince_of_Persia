## 4. Implementation Details

### 4.1. Triple Buffering

This method allowed us to eradicate the Flicker Screen phenomenon, by building two buffers with the same size of the video memory. All of our xpms are drawn in this buffer (except for the cursor, which is drawn in the second buffer, as a way to achieve two levels of animations), instead of directly into the video memory. Every time the mouse moves, we copy the content of the first buffer to the second buffer (using **swap_buffers(bool buffer)**). Then, every timer interrupt, we then copy the content of the second buffer into the video memory (using, once more, **swap_buffers(bool buffer)**). By repeating this cycle indefinitely, we achieve triple buffering.

### 4.2. RTC

The RTC uses the interrupt mechanism to facilitate two primary tasks, managing the in-game timer and updating the current date and time. Since the specific requirements of these tasks only require updates every second the RTC is configured with the update interrupt (UI). To handle and manage what happens after an interrupt is set out the RTC incorporates a designated handler called **rtc_ih()**. When in game mode the rtc handler starts the process of updating the timer using the **increase_timer()**. This function also calls the function **draw_timer()** so that whenever a second has passed the new time is displayed in game. This is achieved by calling the function **draw_timer()**. Lastly, there is also a function to load the number sprites.