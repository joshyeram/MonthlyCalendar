# MonthlyCalendar

After school ended, I wanted to make something that would keep track of my new year's resolution. So I decided to make a calendar to keep track of my resolution.

https://youtu.be/uk93dJq7Fd0

https://www.reddit.com/r/arduino/comments/ko2izf/monthly_calendar_the_monthly_version_of_the_every/

https://www.reddit.com/r/3Dprinting/comments/ko2m4w/this_project_was_the_first_time_i_ever_processed/
- resources for reference

So if you wanted to make this yourself, you need these things:
- Arduino Nano
- a NeoPixel strip of 31 LEDs
- 2 Touch sensors
- wires and etc
- 3D printed parts
- super glue
- m4 screw (or any screw that would enclose the holder) and a nail to the wall
- spray paint(filler primer and any paint of your choosing)
- sandpaper
- long USB cable
- hot glue
- and some thinking

So overall
1. print out the pieces
2. join the pieces in the middle with super glue 
3. sand
4. prime
5. repeat 3 and 4 until smooth
6. paint
Electronics
7. From here, it is better if you look at the code (final.ino)
- NeoPixel strip on D6
- touch sensors on A2 and A4
- I used a USB to power the whole project
    - You can either power it with the plug
    - or strip the wire to + and - then solder it directly to the 5v and ground pins (I did this because why not but either way should work fine)
    - so for the math: 20 milliamps per led and 70 for operation = 20*31 + 70 = 690 so use a 1 amp power source to be safe.
8. On the top, you will see a hole: I wanted to add a photoelectric sensor (to automatically dim the light) but I did not have the resistor to do it so I just left it there for people to try.
9. Glue on the strip
10. push in everything in the cubby
11. upload code: you will have to update the EEPROM(from 0 to 370) to 0 before you even try to upload final.ino
12. cover it with the cover.stl
13. hot glue everything
14. nail on the wall
15. you are done!

There may be things I did not cover so feel free to reach out to me either on reddit(u/joshyeram I check regularly so do not be scared to reach out lol) or youtube!

Feel free to at me at @joshyeram on most platforms (reddit/insta/twitter)! 
