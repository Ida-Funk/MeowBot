void meow(){
    for (int m = 0; m < 4; m++) {
        for (int freq = 1200; freq >= 600; freq -= 5) {
            tone(BUZZER_PIN, freq);
            delay(3);
        }
        noTone(BUZZER_PIN);

        if(m < 3){
            delay (400); 
        }
    }
}
