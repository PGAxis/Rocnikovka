import java.time.Instant;
import java.time.Duration;

public class Main {
    public static void main(String[] args) {
        int iterations = 1000000000;
        double pi = 0.0;

        Instant timeItStarted = Instant.now();

        for (int i = 0; i < iterations; i++) {
            //System.out.println("Počítám, krok " + i);
            if (i % 2 == 0) {
                pi += 1.0 / (2 * i + 1);
            } else {
                pi -= 1.0 / (2 * i + 1);
            }
        }
        pi *= 4;

        Instant currentTime = Instant.now();
        Duration timeItTook = Duration.between(timeItStarted, currentTime);

        int hours = (int) timeItTook.toHours();
        int minutes = (int) timeItTook.toMinutes() % 60;
        int seconds = (int) timeItTook.getSeconds() % 60;

        long millis = timeItTook.toMillis();     //(int) (timeItTook.toMillis() % 1000)
        String millisS = Long.toString(millis);

        if (millis >= 1000)
        {
            millisS = millisS.substring(millisS.length() - 3);
        }
        else if (millis < 100 && millis > 10)
        {
            millisS = "0" + millisS;
        }
        else if (millis < 10)
        {
            millisS = "00" + millisS;
        }


        System.out.println("Approximation of Pi: " + pi + ", time it took: " + hours + ":" + minutes + ":" + seconds + ":" + millisS);
    }
}