const int lightLength = 30;
//const int numberOfPlayers = 2;
const int scoreThreshold = 3;

// game properties
int gameData[lightLength];

int player1Score;

int player2Score;

bool pToggle;

int playerNumber;

bool gameDone = false;

void AISetup() {
  //set up game data
  player1Score = 0;
  player2Score = 0;

  pToggle = true;

  togglePlayer();

  gameDone = false;

  for (int i = 0; i < lightLength; i++)
    gameData[i] = 0;
}
// changes player
void togglePlayer() {
  if (pToggle) {
    playerNumber = 1;
  } else {
    playerNumber = 2;
  }
  pToggle = !pToggle;
}
int getEnemyNumber() {
  if (playerNumber == 1) {
    return 2;
  } else {
    return 1;
  }
}
// player chooses a spot on the light strip
void playerSelect() {
  int s;
  if (playerNumber == 1) {
    if (player1Score > player2Score) {
      s = smartMove(2);
    } else {
      s = smartMove(1);
    }
  } else {
    if (player2Score > player1Score) {
      s = smartMove(1);
    } else {
      s = smartMove(2);
    }
  }
  // smartMove didnt find a spot
  if (s == -1) {
    s = random(lightLength);
    while (gameData[s] != 0) {
      s = random(lightLength);
    }
  }
  return s;
}
//uses player select to place number int selcted spot
void playerPlace(int s){
  gameData[s] = playerNumber;

  check(s);

  togglePlayer();
}

//player makes move depending on n
int smartMove(int n) {

  int p[4];
  p[0] = -1;
  p[1] = -1;
  p[2] = -1;
  p[3] = -1;
  int pL = 4;
  int pInv = 0;
  int i = 0;
  bool foundSpot = false;
  //selects a slot next to enemy spot
  while (pInv < pL-1 && i < lightLength-1) {
    
    if (i != 0 || i != lightLength - 1) {
      if (gameData[i] == 0 && (gameData[i - 1] == n || gameData[i + 1] == n)) {
        p[pInv] = i;
        pInv++;
        foundSpot = true;
      }
    } else if (i == 0) {
      if (gameData[i] == 0 && gameData[i + 1] == n) {
        p[pInv] = i;
        pInv++;
        foundSpot = true;
      }
    } else if (i == lightLength - 1) {
      if (gameData[i] == 0 && gameData[i - 1] == n) {
        p[pInv] = i;
        pInv++;
        foundSpot = true;
      }
    }
    i++;
  }
  if (foundSpot) {
    int r = random(pL);
    return p[r];
  }
  return -1;
}
// checks the left and right to tell if you can add points
void check(int s) {
  int count = 1;
  int i = s;
  Serial.println(playerNumber);
  if (i > 0) {
    while (gameData[--i] == playerNumber) {
      count++;
      if (i < 0) {
        break;
      }
    }
    i = s;
  }
  if (i < lightLength-1) {
    while (gameData[++i] == playerNumber) {
      count++;
      if (i < lightLength-1) {
        break;
      }
    }
  }
  
  if (count >= scoreThreshold) {
    incScore();
  }

}
//add points to current player
void incScore() {
  if (playerNumber == 1) {
    player1Score++;
  } else {
    player2Score++;
  }
}
// this diaplays the array
void displayArray() {
  Serial.print("[");
  for (int i = 0; i < lightLength; i++) {
    Serial.print(gameData[i]);
  }
  Serial.println("]");
}
bool isGameDone() {
  for (int i = 0; i < lightLength; i++) {
    if (gameData[i] == 0)
      return false;
  }
  return true;
}
