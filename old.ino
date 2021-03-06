
state* reset_state(void) {
  int i, j;
  state* p = (state*)malloc(sizeof(state));
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 8; j++) {
      p->grid[i][j] = 0;
    }
  }
  p->direction = NORTH;
  p->current_point.x = 0;
  p->current_point.y = 0;
  ps(p);
  return p;
}
void ps(state* stts) {
  stts->grid[stts->current_point.x][stts->current_point.y] = CP;
}

void print_grid(state* stts) {
  int i, j;
  for (j = 7; j >= 0; j--) {
    for (i = 0; i < 5; i++) {
      if (stts->grid[i][j] == OBSTACLE)
        Serial.print("x ");
      else
        Serial.print(stts->grid[i][j]); Serial.print(" ");
    }
    Serial.print("\n");
  }
}


double manhattan(point des, point from) {
  return (sqrt(pow(abs(des.x - from.x), 2) + pow(abs(des.y - from.y), 2)));
}


int inside_field(point p, int n1, int n2) {
  if (p.x + n1 > 4 || p.x + n1 < 0 || p.y + n2 > 7 || p.y + n2 < 0) {
    return FALSE;}
  return TRUE;
}

int step(state* stts) {
  double minF = 100000;
  int i, j, check = 0, ti, tj;
  double g = 0, h, f, f_1, f_2;
  point saved_point, temp, temp2;

  for (i = -1; i <= 1; i++) {
    for (j = -1; j <= 1; j++) {
      if ((i != 0 && j == 0) || (i == 0 && j != 0)) {
        if (inside_field(stts->current_point, i, j) == TRUE &&
           stts->grid[stts->current_point.x + i][stts->current_point.y + j] !=     
           OBSTACLE) 
         { 
int step(state* stts) {
  double minF = 100000;
  int i, j, check = 0, ti, tj;
  double g = 0, h, f, f_1, f_2;
  point saved_point, temp, temp2;

  for (i = -1; i <= 1; i++) {
    for (j = -1; j <= 1; j++) {
      if ((i != 0 && j == 0) || (i == 0 && j != 0)) {
        if (inside_field(stts->current_point, i, j) == TRUE &&
           stts->grid[stts->current_point.x + i][stts->current_point.y + j] !=     
           OBSTACLE) 
         { 
          temp.x = stts->current_point.x + i; temp.y = stts->current_point.y + j; 
          h = manhattan(stts->current_goal, temp);
          if (stts->grid[stts->current_point.x + i][stts->current_point.y + j] == 
          VISITED) 
          {
            g = 1;
          }
          else g = 0;
          f = h + g;
          if (f < minF) {
            minF = f;
            check = 1;
            saved_point.x = i;
            saved_point.y = j;
            temp2 = temp;
          }
          else if ( f == minF) {
            f_1 = double_step(stts, temp);
            f_2 = double_step(stts, temp2);
            if (f_1 < f_2) {
              check = 1;
              saved_point.x = i;
              saved_point.y = j;
              temp2 = temp;
            }
          }
        }
      }
    }
  }

  int difx, dify;

  if (check == 1) { // Got a candidate
    Serial.print("Got a candiate\n");
    if (saved_point.x == -1) {
      Serial.print("West");
      go_W(stts);
    }
    else if (saved_point.x == 1) {
      Serial.print("EAST");
      go_E(stts);
    }
    else if (saved_point.y == -1) {
      Serial.print("SOUTH");
      go_S(stts);
    }
    else if (saved_point.y == 1) {
      Serial.print("NORTH");
      go_N(stts);
    }
    return 0;
  }
  else { 
    Serial.print("Backtracking\n");
    if (stts->length_of_path >= 0) {
      difx = (stts->current_point.x) - (stts->path[stts->length_of_path].x); 
      dify = (stts->current_point.y) - (stts->path[stts->length_of_path].y);
      if (difx == -1) {
        Serial.print("West");
        go_W(stts);
      }
      else if (difx == 1) {
        Serial.print("West");
        go_E(stts);
      }
      else if (dify == -1) {
        Serial.print("North");
        go_N(stts);
      }
      else if (dify == 1) {
        Serial.print("South");
        go_S(stts);
      }
      stts->path[stts->length_of_path].x = '\0';
      stts->path[stts->length_of_path].y = '\0';
      stts->length_of_path--;
      return 0;
    }
    else {
      return -1;
    }
  }
  Serial.print("Wy here?\n");
  return 0;
}


double double_step(state* stts, point check_point) {
  double minF = 100000;/
  int i, j, check = 0, ti, tj;
  double g = 0, h, f;
  point saved_point, temp;

  for (i = -1; i <= 1; i++) {
    for (j = -1; j <= 1; j++) {
      if ((i != 0 && j == 0) || (i == 0 && j != 0)) { 
        if (inside_field(check_point, i, j) == TRUE && stts->grid[check_point.x + 
           i][check_point.y + j] != OBSTACLE) 
         {
          temp.x = check_point.x + i; temp.y = check_point.y + j;
          h = manhattan(stts->current_goal, temp);
          f = h;
          if (f < minF) {
            minF = f;
          }
        }
      }
    }
  }
  return minF;
}

void agent(state* stts) {
  Serial.print("Agent Started\n");
  point goal[101];
  int i, j = 0, k = 0, set = 0, action;

  for (i = 0; i < 5; i++) {
    if (set == 0) { //go up
      for (j = 0; j <= 7; j++) {
        goal[k].x = i;
        goal[k].y = j;
        k++;
      }
      set = 1;
    }
    else if (set == 1) {
      for (j = 7; j >= 0; j--) {
        goal[k].x = i;
        goal[k].y = j;
        k++;
      }
      set = 0;
    }
  }

  for (i = 1; i < 40;) {
    stts->current_goal = goal[i]; 
    action = step(stts);

    if ((stts->current_point.x == goal[i].x && stts->current_point.y == goal[i].y) 
       || (stts->grid[stts->current_goal.x][stts->current_goal.y] == OBSTACLE)) 
    {
      i++;
    }
    if (action == -1) {
      break;
    }
    ps(stts);
  }
  stopServo();
  while (1);
}


long ms2cm(long microseconds)
{
  return microseconds / 29 / 2;
}

int sense(void)
{
  long duration, cm;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(100);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  cm = ms2cm(duration);
  if (cm <= 20)
  {
    return OBSTACLE;
  }
  return 0;
}

void _go(void)
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
}

void adjust(int ValueRight, int ValueLeft)
{
  if (ValueRight >= THRESHOLD && ValueLeft < THRESHOLD)
  {
    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1490); 
  }
  if (ValueRight < THRESHOLD && ValueLeft >= THRESHOLD)
  {
    servoLeft.writeMicroseconds(1510);
    servoRight.writeMicroseconds(1400);
  }
}

void go(void)
{
  int ValueRight = analogRead(lineRight);
  int ValueLeft = analogRead(lineLeft);
  while (1)
  {
    _go();
    ValueRight = analogRead(lineRight);
    ValueLeft = analogRead(lineLeft);
    Serial.print(ValueRight);
    Serial.print(ValueLeft);
    adjust(ValueRight, ValueLeft); 
    delay(5);

    if (ValueRight >= THRESHOLD && ValueLeft >= THRESHOLD) 
    {
      _go();
      delay(240); 
      stopServo(); 
      break;
    }
  }
}

void t_left(state* stts)
{
  Serial.print("left");
  if (stts->direction == EAST)
    stts->direction = NORTH;
  else if (stts->direction == SOUTH)
    stts->direction = EAST;
  else if (stts->direction == WEST)
    stts->direction = SOUTH;
  else if (stts->direction == NORTH)
    stts->direction = WEST;
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(600);
  stopServo();}

void t_right(state* stts)
{

  Serial.print("right");
  if (stts->direction == EAST)
    stts->direction = SOUTH;
  else if (stts->direction == SOUTH)
    stts->direction = WEST;
  else if (stts->direction == WEST)
    stts->direction = NORTH;
  else if (stts->direction == NORTH)
    stts->direction = EAST;
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(600);
  stopServo();
}

void stopServo(void)
{
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void set_obstacle(state* stts) {
  if (stts->direction == SOUTH) {
    stts->grid[stts->current_point.x][stts->current_point.y - 1] = OBSTACLE;
  }
  else  if (stts->direction == NORTH) {
    stts->grid[stts->current_point.x][stts->current_point.y + 1] = OBSTACLE;
  }
  else if (stts->direction == EAST) {
    stts->grid[stts->current_point.x + 1][stts->current_point.y] = OBSTACLE;
  }
  else if (stts->direction == WEST) {
    stts->grid[stts->current_point.x - 1][stts->current_point.y] = OBSTACLE;
  }
}


void go_E(state* stts)
{
  if (stts->direction == SOUTH)
  {
    t_left(stts);
  }
  else if (stts->direction == WEST)
  {
    t_left(stts); t_left(stts);
  }
  else if (stts->direction == NORTH)
  {
    t_right(stts);
  }
  int check = sense(); //장애물 확인
  if (check != OBSTACLE) {
    stts->path[stts->length_of_path] = stts->current_point;
    stts->grid[stts->current_point.x][stts->current_point.y] = VISITED;
    stts->current_point.x++;
    stts->length_of_path++;
    go();
  }
  else {
    set_obstacle(stts);
  }
}

void go_S(state* stts)
{
  if (stts->direction == WEST)
  {
    t_left(stts);
  }
  else if (stts->direction == NORTH)
  {
    t_left(stts); t_left(stts);
  }
  else if (stts->direction == EAST)
  {
    t_right(stts);
  }
  int check = sense();
  if (check != OBSTACLE) {
    stts->path[stts->length_of_path] = stts->current_point;
    stts->grid[stts->current_point.x][stts->current_point.y] = VISITED;
    stts->current_point.y--;
    stts->length_of_path++;
    go();
  }
  else {
    set_obstacle(stts);
  }
}

void go_W(state* stts)
{
  if (stts->direction == NORTH)
  {
    t_left(stts);
  }
  else if (stts->direction == EAST)
  {
    t_left(stts); t_left(stts);
  }
  else if (stts->direction == SOUTH)
  {
    t_right(stts);
  }
  int check = sense();
  if (check != OBSTACLE) {
    stts->path[stts->length_of_path] = stts->current_point;
    stts->grid[stts->current_point.x][stts->current_point.y] = VISITED;
    stts->current_point.x--;
    stts->length_of_path++;
    go();
  }
  else {
    set_obstacle(stts);
  }
}

void go_N(state* stts)
{
  if (stts->direction == EAST)
  {
    t_left(stts);
  }
  else if (stts->direction == SOUTH)
  {
    t_left(stts); t_left(stts);
  }
  else if (stts->direction == WEST)
  {
    t_right(stts);
  }
  int check = sense();
  if (check != OBSTACLE) {
    stts->path[stts->length_of_path] = stts->current_point;
    stts->grid[stts->current_point.x][stts->current_point.y] = VISITED;
    stts->current_point.y++;
    stts->length_of_path++;
    go();
  }
  else {
    set_obstacle(stts);
  }
}
