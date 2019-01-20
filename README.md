# Race
This program takes a list of lap times as input and calculates the final classification for a race.

The solution for the Kart problem was developed in C++ on Windows with the Visual Studio IDE.

The program has two command line arguments:

<input> Path to the input file containing the race data
<output> Name of the output file containing the processed information

Example:

Windows environment: race.exe race.txt results.txt
Linux environment: ./race race.txt results.txt

The output contains the following information: <pilot final position> <pilot id> <pilot name> <laps completed> <total time for the race> <how much time the pilot spent to reach the end after the winner>

For the input contained in race.txt we get:

```
1	038	F.MASSA 	      4     0:04:11.578	    +(0:00:00.000) 
2	002	K.RAIKKONEN   	      4     0:04:15.152	    +(0:00:03.574)
3	033	R.BARRICHELLO         4     0:04:16.080	    +(0:00:04.502)
4	023	M.WEBBER 	      4     0:04:17.721	    +(0:00:06.143)
5	015	F.ALONSO 	      4     0:04:54.221	    +(0:00:42.643)
6	011	S.VETTEL 	      3     0:06:27.276	    +(0:02:15.697)
```

The solution involves two basic classes: Race and Pilot. Since we do not need to display individual properties for each lap after processing the input, there is not a class to storage their values.

The class Race is responsible for reading the race input file and update the pilots according to it.
