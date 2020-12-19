const int signal_input = A0;
const int LED = 13;
int read_count; // counts reads for averaging
int last_read; // compares current read from last read
int total_read;
int total_count = 100; // number of samples wanted, set n-1 off by 1
int read_avg;
int audio_read = analogRead(signal_input);
int sensitivity = 3; // sets the sensitivity of signal at this threshold
int sample_rate = 10; //sample rate in ms e.g. 10 = a reading every 10ms, 100 samples in 1second 
uint32_t sample_capture_timer;
uint32_t timer_off; 
uint32_t timer_on; 
int on_delay = 200; // don't do anything for in milliseconds e.g. wait 2 seconds before turning on


void setup() {
  pinMode(signal_input, INPUT);
  pinMode(LED, OUTPUT);
  sample_capture_timer = millis();
  //Serial.begin(9600);

}

void loop() {
  sample_capture();
  timer_off_function();
  do_something_with_signal();

}
void do_something_with_signal() {
  if (read_avg > sensitivity && millis() - timer_on > on_delay) { // do something if you see a signal over threshold, and timer delay
    digitalWrite(LED, HIGH); 
    }
  
  if(read_avg < sensitivity){
    digitalWrite (LED, LOW);
    timer_on_flag = true; //enable on timer
  }

  if(timer_on_flag == true){
    timer_on = millis(); // restarts timer for on delay 
    timer_on_flag = false; // do not run this condition 
  }
}

void timer_off_function() {
  if (millis() - timer_off > 5000) {
    digitalWrite(LED, HIGH);
  }
}

void sample_capture() {
  int audio_read = analogRead(signal_input);
  if (millis() - sample_capture_timer > sample_rate) { //controls the sample rate based off the timer
      read_count++;
      total_read = total_read + audio_read; // add samples together for averaging
      off_timer = millis(); // reset off_timer if there is a signal
      sample_capture_timer = millis(); //resets sample_capture timer to run this function again 
    }
  if (read_count > total_count) { //read_count increases and when it matches total_count, average the samples
    read_avg = total_read / (total_count + 1); // average the samples, +1 due to "off by 1 issue" 
    read_count = 0; //reset 
    total_read = 0; //reset 
  }
}  



