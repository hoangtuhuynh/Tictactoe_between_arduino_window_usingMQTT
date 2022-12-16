echo "Enter 'player' for player v player"

read -t 5 choice
  
if [[ $choice == "player" ]]; then
	./test & 
	sleep 2 && mqttx pub -t 'esp/tictactoe' -h 'broker.emqx.io' -p 
1883 
-m "p" &
else
	./test &
	 sleep 2 && mqttx pub -t 'esp/tictactoe' -h 'broker.emqx.io' -p 
1883 -m "a" & fi
