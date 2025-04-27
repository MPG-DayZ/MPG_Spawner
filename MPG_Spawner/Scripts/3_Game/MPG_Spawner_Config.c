class MPG_Spawner_mappingData {
  bool addOnStartup;
  bool addOnEnter;
  bool addOnFirstSpawn;
  bool addOnWin;
  float addDelay;
  bool removeOnEnter;
  bool removeOnFirstSpawn;
  bool removeOnWin;
  float removeDelay;
  ref array<ref ITEM_SpawnerObject> mappingObjects;
}

class MPG_Spawner_PointConfig {
  int pointId;
  bool isDebugEnabled;
  bool isDisabled;
  bool showVisualisation;
  string notificationTitle;
  string notificationTextEnter;
  string notificationTextExit;
  string notificationTextSpawn;
  string notificationTextWin;
  int notificationTime;
  string notificationIcon;
  ref TIntArray triggerDependencies;
  bool triggerDependenciesAnyOf;
  ref TIntArray triggersToEnableOnEnter;
  ref TIntArray triggersToEnableOnFirstSpawn;
  ref TIntArray triggersToEnableOnWin;
  ref TIntArray triggersToEnableOnLeave;
  string triggerPosition;
  string triggerDebugColor;
  string triggerRadius;
  string triggerHeight;
  string triggerWidthX;
  string triggerWidthY;
  string triggerFirstDelay;
  string triggerCooldown;
  float triggerSafeDistance;
  int triggerEnterDelay;
  bool triggerCleanupOnLeave;
  bool triggerCleanupOnLunchTime;
  bool triggerCleanupImmersive;
  int triggerCleanupDelay;
  string triggerWorkingTime;
  bool triggerDisableOnWin;
  bool triggerDisableOnLeave;
  ref TStringArray spawnPositions;
  float spawnRadius;
  int spawnMin;
  int spawnMax;
  int spawnCountLimit;
  bool spawnLoopInside;
  ref TStringArray spawnList;
  int clearDeathAnimals;
  int clearDeathZombies;
  ref array<ref MPG_Spawner_mappingData> mappingData;

  int GetId() { return pointId; }

  void convertFromV1(MPG_Spawner_PointConfigV1 pcv1) {
    pointId = pcv1.pointId;
    isDebugEnabled = pcv1.isDebugEnabled;
    notificationTitle = pcv1.notificationTitle;
    notificationTextEnter = pcv1.notificationTextEnter;
    notificationTextExit = pcv1.notificationTextExit;
    notificationTextSpawn = pcv1.notificationTextSpawn;
    notificationTextWin = pcv1.notificationTextWin;
    notificationTime = pcv1.notificationTime;
    notificationIcon = pcv1.notificationIcon;
    triggerDependencies = pcv1.triggerDependencies;
    triggerDependenciesAnyOf = pcv1.triggerDependenciesAnyOf;
    triggersToEnableOnEnter = pcv1.triggersToEnableOnEnter;
    triggersToEnableOnFirstSpawn = pcv1.triggersToEnableOnFirstSpawn;
    triggersToEnableOnWin = pcv1.triggersToEnableOnWin;
    triggersToEnableOnLeave = pcv1.triggersToEnableOnLeave;
    triggerPosition = pcv1.triggerPosition;
    triggerDebugColor = pcv1.triggerDebugColor;
    // в v2 это строка, поэтому конвертируем в строку
    triggerRadius = pcv1.triggerRadius.ToString();
    // в v2 это строка, поэтому конвертируем в строку
    triggerHeight = pcv1.triggerHeight.ToString();
    // в v2 это строка, поэтому конвертируем в строку
    triggerWidthX = pcv1.triggerWidthX.ToString();
    // в v2 это строка, поэтому конвертируем в строку
    triggerWidthY = pcv1.triggerWidthY.ToString();
    // в v2 это строка, поэтому конвертируем в строку
    triggerFirstDelay = pcv1.triggerFirstDelay.ToString();
    // в v2 это строка, поэтому конвертируем в строку
    triggerCooldown = pcv1.triggerCooldown.ToString();
    triggerSafeDistance = pcv1.triggerSafeDistance;
    triggerEnterDelay = pcv1.triggerEnterDelay;
    triggerCleanupOnLeave = pcv1.triggerCleanupOnLeave;
    triggerCleanupOnLunchTime = pcv1.triggerCleanupOnLunchTime;
    triggerCleanupImmersive = pcv1.triggerCleanupImmersive;
    triggerCleanupDelay = pcv1.triggerCleanupDelay;
    triggerWorkingTime = pcv1.triggerWorkingTime;
    triggerDisableOnWin = pcv1.triggerDisableOnWin;
    triggerDisableOnLeave = pcv1.triggerDisableOnLeave;
    spawnPositions = pcv1.spawnPositions;
    spawnRadius = pcv1.spawnRadius;
    spawnMin = pcv1.spawnMin;
    spawnMax = pcv1.spawnMax;
    spawnCountLimit = pcv1.spawnCountLimit;
    spawnLoopInside = pcv1.spawnLoopInside;
    spawnList = pcv1.spawnList;
    clearDeathAnimals = pcv1.clearDeathAnimals;
    clearDeathZombies = pcv1.clearDeathZombies;
    mappingData = pcv1.mappingData;
  }

  void convertFromV2(MPG_Spawner_PointConfigV2 pcv2) {
    pointId = pcv2.pointId;
    isDebugEnabled = pcv2.isDebugEnabled;
    notificationTitle = pcv2.notificationTitle;
    notificationTextEnter = pcv2.notificationTextEnter;
    notificationTextExit = pcv2.notificationTextExit;
    notificationTextSpawn = pcv2.notificationTextSpawn;
    notificationTextWin = pcv2.notificationTextWin;
    notificationTime = pcv2.notificationTime;
    notificationIcon = pcv2.notificationIcon;
    triggerDependencies = pcv2.triggerDependencies;
    triggerDependenciesAnyOf = pcv2.triggerDependenciesAnyOf;
    triggersToEnableOnEnter = pcv2.triggersToEnableOnEnter;
    triggersToEnableOnFirstSpawn = pcv2.triggersToEnableOnFirstSpawn;
    triggersToEnableOnWin = pcv2.triggersToEnableOnWin;
    triggersToEnableOnLeave = pcv2.triggersToEnableOnLeave;
    triggerPosition = pcv2.triggerPosition;
    triggerDebugColor = pcv2.triggerDebugColor;
    // в v2 это строка, поэтому конвертируем в строку
    triggerRadius = pcv2.triggerRadius.ToString();
    // в v2 это строка, поэтому конвертируем в строку
    triggerHeight = pcv2.triggerHeight.ToString();
    // в v2 это строка, поэтому конвертируем в строку
    triggerWidthX = pcv2.triggerWidthX.ToString();
    // в v2 это строка, поэтому конвертируем в строку
    triggerWidthY = pcv2.triggerWidthY.ToString();
    triggerFirstDelay = pcv2.triggerFirstDelay;
    triggerCooldown = pcv2.triggerCooldown;
    triggerSafeDistance = pcv2.triggerSafeDistance;
    triggerEnterDelay = pcv2.triggerEnterDelay;
    triggerCleanupOnLeave = pcv2.triggerCleanupOnLeave;
    triggerCleanupOnLunchTime = pcv2.triggerCleanupOnLunchTime;
    triggerCleanupImmersive = pcv2.triggerCleanupImmersive;
    triggerCleanupDelay = pcv2.triggerCleanupDelay;
    triggerWorkingTime = pcv2.triggerWorkingTime;
    triggerDisableOnWin = pcv2.triggerDisableOnWin;
    triggerDisableOnLeave = pcv2.triggerDisableOnLeave;
    spawnPositions = pcv2.spawnPositions;
    spawnRadius = pcv2.spawnRadius;
    spawnMin = pcv2.spawnMin;
    spawnMax = pcv2.spawnMax;
    spawnCountLimit = pcv2.spawnCountLimit;
    spawnLoopInside = pcv2.spawnLoopInside;
    spawnList = pcv2.spawnList;
    clearDeathAnimals = pcv2.clearDeathAnimals;
    clearDeathZombies = pcv2.clearDeathZombies;
    mappingData = pcv2.mappingData;
  }
}

class MPG_Spawner_PointConfigV1 {
  int pointId;
  bool isDebugEnabled;
  string notificationTitle;
  string notificationTextEnter;
  string notificationTextExit;
  string notificationTextSpawn;
  string notificationTextWin;
  int notificationTime;
  string notificationIcon;
  ref TIntArray triggerDependencies;
  bool triggerDependenciesAnyOf;
  ref TIntArray triggersToEnableOnEnter;
  ref TIntArray triggersToEnableOnFirstSpawn;
  ref TIntArray triggersToEnableOnWin;
  ref TIntArray triggersToEnableOnLeave;
  string triggerPosition;
  string triggerDebugColor;
  float triggerRadius;
  float triggerHeight;
  float triggerWidthX;
  float triggerWidthY;
  int triggerFirstDelay;
  float triggerCooldown;
  float triggerSafeDistance;
  int triggerEnterDelay;
  bool triggerCleanupOnLeave;
  bool triggerCleanupOnLunchTime;
  bool triggerCleanupImmersive;
  int triggerCleanupDelay;
  string triggerWorkingTime;
  bool triggerDisableOnWin;
  bool triggerDisableOnLeave;
  ref TStringArray spawnPositions;
  float spawnRadius;
  int spawnMin;
  int spawnMax;
  int spawnCountLimit;
  bool spawnLoopInside;
  ref TStringArray spawnList;
  int clearDeathAnimals;
  int clearDeathZombies;
  ref array<ref MPG_Spawner_mappingData> mappingData;

  int GetId() { return pointId; }
}

class MPG_Spawner_PointConfigV2 {
  int pointId;
  bool isDebugEnabled;
  string notificationTitle;
  string notificationTextEnter;
  string notificationTextExit;
  string notificationTextSpawn;
  string notificationTextWin;
  int notificationTime;
  string notificationIcon;
  ref TIntArray triggerDependencies;
  bool triggerDependenciesAnyOf;
  ref TIntArray triggersToEnableOnEnter;
  ref TIntArray triggersToEnableOnFirstSpawn;
  ref TIntArray triggersToEnableOnWin;
  ref TIntArray triggersToEnableOnLeave;
  string triggerPosition;
  string triggerDebugColor;
  float triggerRadius;
  float triggerHeight;
  float triggerWidthX;
  float triggerWidthY;
  string triggerFirstDelay;
  string triggerCooldown;
  float triggerSafeDistance;
  int triggerEnterDelay;
  bool triggerCleanupOnLeave;
  bool triggerCleanupOnLunchTime;
  bool triggerCleanupImmersive;
  int triggerCleanupDelay;
  string triggerWorkingTime;
  bool triggerDisableOnWin;
  bool triggerDisableOnLeave;
  ref TStringArray spawnPositions;
  float spawnRadius;
  int spawnMin;
  int spawnMax;
  int spawnCountLimit;
  bool spawnLoopInside;
  ref TStringArray spawnList;
  int clearDeathAnimals;
  int clearDeathZombies;
  ref array<ref MPG_Spawner_mappingData> mappingData;

  int GetId() { return pointId; }
}

class MPG_SPWNR_ModConfig {

  int configVersion = 4;
  string documentation = "https://docs.mpg-dayz.ru/spawner/";
  bool isModDisabled = false;
  bool isDebugEnabled = false;
  ref TStringArray pointsConfigs = new TStringArray;

  void MPG_SPWNR_ModConfig() {
    if (GetGame().IsServer() && GetGame().IsMultiplayer()) {
      Print(MPG_SPWNR + " Init");
      LoadConfig();
      UpdateConfig();
    }
  }

  // clang-format off
  private void LoadConfig() {
    // clang-format on
    if (GetGame().IsServer() && GetGame().IsMultiplayer()) {
      if (FileExist(MPG_SPWNR_CONFIG_FILENAME)) {
        Print(MPG_SPWNR + " config found, loading...");
        JsonFileLoader<MPG_SPWNR_ModConfig>.JsonLoadFile(MPG_SPWNR_CONFIG_FILENAME, this);
      } else {
        Print(MPG_SPWNR + " config NOT found, creating...");
        CreateMPG_SPWNR_ModConfig();
      }
    }
  }

  // clang-format off
  private void UpdateConfig() {
    // clang-format on
    if (this.configVersion == 1) {
      configVersion = 4;
      JsonFileLoader<MPG_SPWNR_ModConfig>.JsonSaveFile(MPG_SPWNR_CONFIG_FILENAME, this);
      // clang-format off
      foreach (string pointConfigFile : pointsConfigs) {
        // clang-format on
        if (FileExist(MPG_SPWNR_POINTS_DIR + pointConfigFile + ".json")) {
          array<ref MPG_Spawner_PointConfigV1> pointConfigV1 = new array<ref MPG_Spawner_PointConfigV1>;
          JsonFileLoader<array<ref MPG_Spawner_PointConfigV1>>.JsonLoadFile(MPG_SPWNR_POINTS_DIR + pointConfigFile + ".json", pointConfigV1);

          array<ref MPG_Spawner_PointConfig> pointConfigV2 = new array<ref MPG_Spawner_PointConfig>;

          // clang-format off
          foreach (MPG_Spawner_PointConfigV1 pointConfigV1Item : pointConfigV1) {
            // clang-format on
            MPG_Spawner_PointConfig converted = new MPG_Spawner_PointConfig();
            converted.convertFromV1(pointConfigV1Item);

            pointConfigV2.Insert(converted);
          }

          JsonFileLoader<array<ref MPG_Spawner_PointConfig>>.JsonSaveFile(MPG_SPWNR_POINTS_DIR + pointConfigFile + ".json", pointConfigV2);
          Print(MPG_SPWNR + " config file '" + pointConfigFile + "' updated from v1 to v3");
        }
      }
      Print(MPG_SPWNR + " config files updated from v1 to v3");
      UpdateConfig();
    }
    if (this.configVersion == 2) {
      configVersion = 4;
      JsonFileLoader<MPG_SPWNR_ModConfig>.JsonSaveFile(MPG_SPWNR_CONFIG_FILENAME, this);
      // clang-format off
      foreach (string pointConfigFileV2 : pointsConfigs) {
        // clang-format on
        if (FileExist(MPG_SPWNR_POINTS_DIR + pointConfigFileV2 + ".json")) {
          array<ref MPG_Spawner_PointConfigV2> pointConfigV2to3 = new array<ref MPG_Spawner_PointConfigV2>;
          JsonFileLoader<array<ref MPG_Spawner_PointConfigV2>>.JsonLoadFile(MPG_SPWNR_POINTS_DIR + pointConfigFileV2 + ".json", pointConfigV2to3);

          array<ref MPG_Spawner_PointConfig> pointConfigV3 = new array<ref MPG_Spawner_PointConfig>;

          // clang-format off
          foreach (MPG_Spawner_PointConfigV2 pointConfigV3Item : pointConfigV2to3) {
            // clang-format on
            MPG_Spawner_PointConfig convertedV2 = new MPG_Spawner_PointConfig();
            convertedV2.convertFromV2(pointConfigV3Item);

            pointConfigV3.Insert(convertedV2);
          }

          JsonFileLoader<array<ref MPG_Spawner_PointConfig>>.JsonSaveFile(MPG_SPWNR_POINTS_DIR + pointConfigFileV2 + ".json", pointConfigV3);
          Print(MPG_SPWNR + " config file '" + pointConfigFileV2 + "' updated from v2 to v3");
        }
      }
      Print(MPG_SPWNR + " config files updated from v2 to v3");
    }
    if (this.configVersion == 3) {
      configVersion = 4;
      JsonFileLoader<MPG_SPWNR_ModConfig>.JsonSaveFile(MPG_SPWNR_CONFIG_FILENAME, this);
    }
  }

  // clang-format off
  private void CreateMPG_SPWNR_ModConfig() {
    // clang-format on

    if (!FileExist(MPG_SPWNR_ROOT_DIR)) {
      Print(MPG_SPWNR + "'" + MPG_SPWNR_ROOT_DIR + "' does not exist, creating...");
      MakeDirectory(MPG_SPWNR_ROOT_DIR);
    }
    if (!FileExist(MPG_SPWNR_POINTS_DIR)) {
      Print(MPG_SPWNR + "'" + MPG_SPWNR_POINTS_DIR + "' does not exist, creating...");
      MakeDirectory(MPG_SPWNR_POINTS_DIR);
    }

    // Точка 1
    MPG_Spawner_PointConfig point1 = new MPG_Spawner_PointConfig();
    point1.pointId = 1;
    point1.isDebugEnabled = true;
    point1.notificationTitle = "Точка 1";
    point1.notificationTextEnter = "Вы вошли в точку 1. Тут вас ждут медведи!";
    point1.notificationTextExit = "Вы покинули точку 1. Надеемся на своих двоих!";
    point1.notificationTextSpawn = "Где-то рядом %2 %1 %3.;появил|ся|ось|ось;медвед|ь|я|ей";
    point1.notificationTextWin = "Замечательно! Вы убили всех медведей!";
    point1.notificationTime = 8;
    point1.notificationIcon = "set:dayz_gui image:iconSkull";
    point1.triggerDependencies = {};
    point1.triggerPosition = "4246.0 333.7 5586.7";
    point1.triggerDebugColor = "red";
    point1.triggerRadius = "50.0";
    point1.triggerFirstDelay = "10-15";
    point1.triggerCooldown = "60-70";
    point1.triggerSafeDistance = 25;
    point1.triggerEnterDelay = 0;
    point1.triggerWorkingTime = "0-24";
    point1.spawnPositions = { "4246.0 0.0 5586.7" };
    point1.spawnRadius = 100.0;
    point1.spawnMin = 2;
    point1.spawnMax = 5;
    point1.spawnCountLimit = 30;
    point1.spawnLoopInside = true;
    point1.spawnList = { "Animal_UrsusArctos", "Animal_CanisLupus_Grey" };
    point1.clearDeathAnimals = 0;
    point1.clearDeathZombies = 0;

    // Точка 2
    MPG_Spawner_PointConfig point2 = new MPG_Spawner_PointConfig();
    point2.pointId = 2;
    point2.isDebugEnabled = true;
    point2.notificationTitle = "Точка 2";
    point2.notificationTextEnter = "Вы вошли в точку 2. Тут вас ждут зомби!";
    point2.notificationTextExit = "Вы покинули точку 2. Надеемся на своих двоих!";
    point2.notificationTextSpawn = "Где-то рядом %2 %1 %3.;появил|ся|ось|ось;зараженны|й|х|х";
    point2.notificationTextWin = "Замечательно! Вы убили всех зараженных!";
    point2.notificationTime = 8;
    point2.notificationIcon = "set:dayz_inventory image:electricity";
    point2.triggerDependencies = {};
    point2.triggerPosition = "7760.487793 0.0 14849.181641";
    point2.triggerDebugColor = "green";
    point2.triggerRadius = "5.0";
    point2.triggerFirstDelay = "0";
    point2.triggerCooldown = "15";
    point2.triggerSafeDistance = 0;
    point2.triggerEnterDelay = 0;
    point2.triggerWorkingTime = "0-24";
    point2.spawnPositions = { "7795.58740 0.0 14859.889648" };
    point2.spawnRadius = 6.0;
    point2.spawnMin = 2;
    point2.spawnMax = 5;
    point2.spawnCountLimit = 30;
    point2.spawnLoopInside = true;
    point2.spawnList = { "ZmbF_MechanicNormal_Beige", "ZmbM_ConstrWorkerNormal_Beige" };
    point2.clearDeathAnimals = 0;
    point2.clearDeathZombies = 10;

    // Точка 3
    MPG_Spawner_PointConfig point3 = new MPG_Spawner_PointConfig();
    point3.pointId = 3;
    point3.isDebugEnabled = true;
    point3.notificationTitle = "Точка 3";
    point3.notificationTextEnter = "Вы вошли в точку 3. Тут вас ждут все подряд!";
    point3.notificationTextExit = "Вы покинули точку 3. Надеемся на своих двоих!";
    point3.notificationTextSpawn = "Где-то рядом появились новые сущности.";
    point3.notificationTextWin = "Замечательно! Вы убили всех врагов :)!";
    point3.notificationTime = 8;
    point3.notificationIcon = "set:dayz_gui image:iconSkull";
    point3.triggerDependencies = { 4 };
    point3.triggerPosition = "2081.737549 194.911041 5404.941895";
    point3.triggerDebugColor = "blue";
    point3.triggerRadius = "20.0";
    point3.triggerFirstDelay = "10-30";
    point3.triggerCooldown = "15-30";
    point3.triggerSafeDistance = 25;
    point3.triggerEnterDelay = 0;
    point3.triggerWorkingTime = "0-24";
    point3.spawnPositions = {
      "2091.094482 191.329178 5378.864746", "2077.824463 192.110657 5382.869629", "2055.367920 191.928192 5386.645996", "2052.493408 193.803436 5402.255859", "2060.412598 195.821899 5416.467773", "2070.752441 197.109344 5424.640625", "2086.490234 198.078369 5430.839355", "2098.352295 196.910309 5427.170410", "2109.596191 194.844818 5419.104980", "2112.131592 193.133255 5403.931641", "2108.542236 192.027100 5390.762695", "2099.439941 191.435379 5382.692383", "2087.581299 191.514465 5379.543945", "2095.927734 193.400543 5397.945313", "2098.221436 189.324829 5365.816895", "2075.012207 189.867905 5365.750488", "2054.232422 190.407227 5376.447754", "2042.844360 194.466370 5411.201660", "2062.012207 198.461563 5437.993164", "2098.273438 197.840637 5437.447266", "2119.691162 194.252502 5416.017578", "2122.454346 192.361069 5392.525391", "2113.915039 190.541046 5373.567871", "2093.498535 189.385101 5365.031738"
    };
    point3.spawnRadius = 2.0;
    point3.spawnMin = 2;
    point3.spawnMax = 5;
    point3.spawnCountLimit = 30;
    point3.spawnLoopInside = true;
    point3.spawnList = {
      "ZmbF_MechanicNormal_Beige|0.2",
      "ZmbM_ConstrWorkerNormal_Beige|0.5",
      "Animal_UrsusArctos|0.7",
      "Animal_CanisLupus_Grey|0.7"
    };
    point3.clearDeathAnimals = 5;
    point3.clearDeathZombies = 0;

    // Точка 4
    MPG_Spawner_PointConfig point4 = new MPG_Spawner_PointConfig();
    point4.pointId = 4;
    point4.isDebugEnabled = true;
    point4.notificationTitle = "Точка 4";
    point4.notificationTextEnter = "Вы вошли в точку 4.";
    point4.notificationTextExit = "Вы покинули точку 4.";
    point4.notificationTextSpawn = "Где-то рядом %2 %1 %3.;появил|ся|ось|ось;медвед|ь|я|ей";
    point4.notificationTextWin = "Замечательно! Вы завершили миссию!";
    point4.notificationTime = 8;
    point4.notificationIcon = "set:dayz_gui image:iconSkull";
    point4.triggerDependencies = {};
    point4.triggerPosition = "5960.494629 0.0 2055.235352";
    point4.triggerDebugColor = "yellow";
    point4.triggerRadius = "30.0";
    point4.triggerHeight = "15.0";
    point4.triggerFirstDelay = "10";
    point4.triggerCooldown = "15";
    point4.triggerSafeDistance = 25;
    point4.triggerEnterDelay = 3;
    point4.triggerWorkingTime = "0-24";
    point4.spawnPositions = { "5960.494629 0.0 2055.235352" };
    point4.spawnRadius = 50.0;
    point4.spawnMin = 2;
    point4.spawnMax = 5;
    point4.spawnCountLimit = 0;
    point4.spawnLoopInside = true;
    point4.spawnList = { "Animal_UrsusArctos" };
    point4.clearDeathAnimals = 10;
    point4.clearDeathZombies = 0;

    // Точка 5
    MPG_Spawner_PointConfig point5 = new MPG_Spawner_PointConfig();
    point5.pointId = 5;
    point5.isDebugEnabled = true;
    point5.notificationTitle = "Точка 5";
    point5.notificationTextEnter = "Вы вошли в точку 5.";
    point5.notificationTextExit = "Вы покинули точку 5.";
    point5.notificationTextSpawn = "Спавн: %1 шт.;";
    point5.notificationTextWin = "Победа!";
    point5.notificationTime = 3;
    point5.notificationIcon = "set:dayz_gui image:iconSkull";
    point5.triggerPosition = "12867,0.0,9259.791016";
    point5.triggerDebugColor = "red";
    point5.triggerHeight = "5.0";
    point5.triggerWidthX = "20.0";
    point5.triggerWidthY = "10.0";
    point5.triggerFirstDelay = "10-120";
    point5.triggerCooldown = "5-30";
    point5.triggerWorkingTime = "0-24";
    point5.spawnPositions = { "12866.606445, 0.0, 9253.121094",
                              "12862.797852 0 9258.031250",
                              "12865.261719, 7, 9264.573242" };
    point5.spawnRadius = 0;
    point5.spawnMin = 1;
    point5.spawnMax = 3;
    point5.spawnCountLimit = 10;
    point5.spawnLoopInside = true;
    point5.spawnList = { "Animal_UrsusArctos| 1 | -3 | -3 | 0.1-1",
                         "Apple| 1 | -3 | -3 | 30-30 | 30-30",
                         "WaterBottle | 1 | -2 | -2 | -2 | -2",
                         "Mag_AK101_30Rnd | 0.5 | 120 | 30-60 | 10-67",
                         "AKM | 1 | -3 | -2 | -1" };
    point5.clearDeathAnimals = 5;
    point5.clearDeathZombies = 5;
    point5.triggerCleanupOnLeave = true;
    point5.triggerCleanupDelay = 5;

    // Сохраняем конфиги
    pointsConfigs = { "Point_Example1", "Point_Example2" };

    JsonFileLoader<MPG_SPWNR_ModConfig>.JsonSaveFile(MPG_SPWNR_CONFIG_FILENAME, this);
    JsonFileLoader<array<MPG_Spawner_PointConfig>>.JsonSaveFile(MPG_SPWNR_POINTS_DIR + "Point_Example1.json", { point1, point2 });
    JsonFileLoader<array<MPG_Spawner_PointConfig>>.JsonSaveFile(MPG_SPWNR_POINTS_DIR + "Point_Example2.json", { point3, point4, point5 });
  }
}

static ref MPG_SPWNR_ModConfig g_MPG_SPWNR_ModConfig;

static ref MPG_SPWNR_ModConfig GetMPG_SPWNR_ModConfig() {
  if (!g_MPG_SPWNR_ModConfig) {
    g_MPG_SPWNR_ModConfig = new MPG_SPWNR_ModConfig();
  }
  return g_MPG_SPWNR_ModConfig;
}
