enum MPG_TriggerEventType {
  // Trigger event types
  STARTUP,
  ENTER,
  FIRST_SPAWN,
  WIN,
  LEAVE
};

class MPG_Trigger extends Trigger {

  MPG_SPWNR_Logger Logger = MPG_SPWNR_Logger.Cast(GetPlugin(MPG_SPWNR_Logger));
  MPG_SPWNR_ModConfig MPG_SPWNR_Config = g_MPG_SPWNR_ModConfig;

  // Поля совпадают с полями конфига MPG_Spawner_PointConfig
  // clang-format off
  protected int pointId;
  protected bool isDebugEnabled;
  protected bool showVisualisation;
  protected bool isDisabled;
  protected string notificationTitle;
  protected string notificationTextEnter;
  protected string notificationTextExit;
  protected string notificationTextSpawn;
  protected string notificationTextWin;
  protected int notificationTime;
  protected string notificationIcon;
  protected ref TIntArray triggerDependencies;
  protected bool triggerDependenciesAnyOf;
  protected ref TIntArray triggersToEnableOnEnter;
  protected ref TIntArray triggersToEnableOnFirstSpawn;
  protected ref TIntArray triggersToEnableOnWin;
  protected ref TIntArray triggersToEnableOnLeave;
  protected string triggerPosition;
  protected string triggerDebugColor;
  protected string triggerRadius;
  protected string triggerHeight;
  protected string triggerWidthX;
  protected string triggerWidthY;
  protected string triggerFirstDelay;
  protected string triggerCooldown;
  protected float triggerSafeDistance;
  protected int triggerEnterDelay;
  protected bool triggerCleanupOnLeave;
  protected bool triggerCleanupOnLunchTime;
  protected bool triggerCleanupImmersive;
  protected int triggerCleanupDelay;
  protected string triggerWorkingTime;
  protected bool triggerDisableOnWin;
  protected bool triggerDisableOnLeave;
  protected ref TStringArray spawnPositions;
  protected float spawnRadius;
  protected int spawnMin;
  protected int spawnMax;
  protected int spawnCountLimit;
  protected bool spawnLoopInside;
  protected ref TStringArray spawnList;
  protected int clearDeathAnimals;
  protected int clearDeathZombies;
  protected ref array<ref MPG_Spawner_mappingData> mappingData;

  // Поля, специфичные для этого класса.
  protected int nextTriggerTime;
  protected vector debugPos;
  protected string logPrefix;
  protected bool isTriggered;
  protected bool isEntered;

  protected ref array<Object> creaturesToCleanup = {};
  protected ref array<Object> lootToCleanup = {};
  protected ref array<Object> objectsToRemoveOnEnter = {};
  protected ref array<Object> objectsToRemoveOnFirstSpawn = {};
  protected ref array<Object> objectsToRemoveOnWin = {};
  protected ref array<int> objectsToRemoveOnEnterDelay = {};
  protected ref array<int> objectsToRemoveOnFirstSpawnDelay = {};
  protected ref array<int> objectsToRemoveOnWinDelay = {};
  protected ref array<Object> debugObjects = {};
  protected bool isSpawnedOnEnter = false;
  protected bool isSpawnedOnFirstSpawn = false;
  protected bool isSpawnedOnWin = false;
  protected float triggerRadiusRand;
  protected float triggerHeightRand;
  protected float triggerWidthXRand;
  protected float triggerWidthYRand;
  // clang-format on
  // Геттеры
  int GetPointId() { return pointId; };

  int GetNotificationTime() { return notificationTime; }
  string GetNotificationTitle() { return notificationTitle; };
  string GetNotificationTextWin() { return notificationTextWin; };
  string GetNotificationIcon() { return notificationIcon; };
  bool GetIsTriggered() { return isTriggered; }

  // Сеттеры
  void CreateMPGTrigger(MPG_Spawner_PointConfig pointConfig, vector m_debugPos, vector rotation) {
    /// Тоже что и в конфиге ---->
    pointId = pointConfig.pointId;
    isDebugEnabled = pointConfig.isDebugEnabled;
    showVisualisation = pointConfig.showVisualisation;
    isDisabled = pointConfig.isDisabled;
    notificationTitle = pointConfig.notificationTitle;
    notificationTextEnter = pointConfig.notificationTextEnter;
    notificationTextExit = pointConfig.notificationTextExit;
    notificationTextSpawn = pointConfig.notificationTextSpawn;
    notificationTextWin = pointConfig.notificationTextWin;
    notificationTime = pointConfig.notificationTime;
    notificationIcon = pointConfig.notificationIcon;
    triggerDependencies = pointConfig.triggerDependencies;
    triggerDependenciesAnyOf = pointConfig.triggerDependenciesAnyOf;
    triggersToEnableOnEnter = pointConfig.triggersToEnableOnEnter;
    triggersToEnableOnFirstSpawn = pointConfig.triggersToEnableOnFirstSpawn;
    triggersToEnableOnWin = pointConfig.triggersToEnableOnWin;
    triggersToEnableOnLeave = pointConfig.triggersToEnableOnLeave;
    triggerPosition = pointConfig.triggerPosition;
    triggerDebugColor = pointConfig.triggerDebugColor;
    triggerRadius = pointConfig.triggerRadius;
    triggerHeight = pointConfig.triggerHeight;
    triggerWidthX = pointConfig.triggerWidthX;
    triggerWidthY = pointConfig.triggerWidthY;
    triggerFirstDelay = pointConfig.triggerFirstDelay;
    triggerCooldown = pointConfig.triggerCooldown;
    triggerSafeDistance = pointConfig.triggerSafeDistance;
    triggerEnterDelay = pointConfig.triggerEnterDelay;
    triggerCleanupOnLeave = pointConfig.triggerCleanupOnLeave;
    triggerCleanupOnLunchTime = pointConfig.triggerCleanupOnLunchTime;
    triggerCleanupImmersive = pointConfig.triggerCleanupImmersive;
    triggerCleanupDelay = pointConfig.triggerCleanupDelay;
    triggerWorkingTime = pointConfig.triggerWorkingTime;
    triggerDisableOnWin = pointConfig.triggerDisableOnWin;
    triggerDisableOnLeave = pointConfig.triggerDisableOnLeave;
    spawnPositions = pointConfig.spawnPositions;
    spawnRadius = pointConfig.spawnRadius;
    spawnMin = pointConfig.spawnMin;
    spawnMax = pointConfig.spawnMax;
    spawnCountLimit = pointConfig.spawnCountLimit;
    spawnLoopInside = pointConfig.spawnLoopInside;
    spawnList = pointConfig.spawnList;
    clearDeathAnimals = pointConfig.clearDeathAnimals;
    clearDeathZombies = pointConfig.clearDeathZombies;
    mappingData = pointConfig.mappingData;
    // <----

    triggerRadiusRand = GetRandFloat(pointConfig.triggerRadius);
    triggerHeightRand = GetRandFloat(pointConfig.triggerHeight);
    triggerWidthXRand = GetRandFloat(pointConfig.triggerWidthX);
    triggerWidthYRand = GetRandFloat(pointConfig.triggerWidthY);

    debugPos = m_debugPos;
    logPrefix = "PointId: " + pointId + "; ";

    SetNextTriggerTime(GetRandInt(triggerFirstDelay));

    // Вращаем триггер только по одной оси т.к. по другим пока не готово
    SetOrientation(Vector(rotation[0], 0, 0));

    string triggerType = "box";

    if (triggerWidthXRand > 0 && triggerWidthYRand > 0) {
      // Квадратный триггер
      vector etxMin = -Vector(triggerWidthXRand, 0, triggerWidthYRand) * 0.5;
      vector extMax = Vector(triggerWidthXRand, triggerHeightRand * 2, triggerWidthYRand) * 0.5;

      SetExtents(etxMin, extMax);

    } else if (triggerHeightRand > 0) {
      // Цилиндрический триггер
      SetCollisionCylinder(triggerRadiusRand, triggerHeightRand);
      triggerType = "cylinder";
    } else {
      // Сферический триггер
      triggerType = "sphere";
      SetCollisionSphere(triggerRadiusRand);
    };

    LogThis(string.Format("%1Trigger: Created; title: %2; pos: %3; type: %4", logPrefix, notificationTitle, debugPos.ToString(), triggerType));
    LogThis(string.Format("%1Trigger: SetSize; radius: %2; height: %3; widthX: %4; widthY: %5", logPrefix, triggerRadiusRand, triggerHeightRand, triggerWidthXRand, triggerWidthYRand));

    TryToProcessMappingDataObjects(MPG_TriggerEventType.STARTUP);

    DrawDebugShape();

    LogThis(logPrefix + "mappingData: " + mappingData.Count());
  }

  void SetNextTriggerTime(float m_time = 0) { nextTriggerTime = GetGameTime() + m_time }

  void SetDisabled() {
    isDisabled = true;
  }

  void SetEnabled() {
    isDisabled = false;
  }

  // Основной функционал класса

  // Что будем делать при удалении триггера
  void DeleteTrigger() {
    LogThis(logPrefix + "deleteTrigger: START");

    if (creaturesToCleanup.Count()) {
      LogThis(logPrefix + "deleteTrigger: creaturesToCleanup clean");

      foreach (Object del1 : creaturesToCleanup) {
        if (del1) {
          GetGame().ObjectDelete(del1);
        }
      }
      creaturesToCleanup.Clear();
    }

    if (lootToCleanup.Count()) {
      LogThis(logPrefix + "deleteTrigger: lootToCleanup clean");

      foreach (Object del2 : lootToCleanup) {
        if (del2) {
          GetGame().ObjectDelete(del2);
        }
      }
      lootToCleanup.Clear();
    }

    if (objectsToRemoveOnEnter.Count()) {
      LogThis(logPrefix + "deleteTrigger: objectsToRemoveOnEnter clean");

      foreach (Object del3 : objectsToRemoveOnEnter) {
        if (del3) {
          GetGame().ObjectDelete(del3);
        }
      }
      objectsToRemoveOnEnter.Clear();
      objectsToRemoveOnEnterDelay.Clear();
    }

    if (objectsToRemoveOnFirstSpawn.Count()) {
      LogThis(logPrefix + "deleteTrigger: objectsToRemoveOnFirstSpawn clean");

      foreach (Object del4 : objectsToRemoveOnFirstSpawn) {
        if (del4) {
          GetGame().ObjectDelete(del4);
        }
      }
      objectsToRemoveOnFirstSpawn.Clear();
      objectsToRemoveOnFirstSpawnDelay.Clear();
    }

    if (objectsToRemoveOnWin.Count()) {
      LogThis(logPrefix + "deleteTrigger: objectsToRemoveOnWin clean");

      foreach (Object del5 : objectsToRemoveOnWin) {
        if (del5) {
          GetGame().ObjectDelete(del5);
        }
      }
      objectsToRemoveOnWin.Clear();
      objectsToRemoveOnWinDelay.Clear();
    }

    if (debugObjects.Count()) {
      LogThis(logPrefix + "deleteTrigger: debugObjects clean");

      foreach (Object del6 : debugObjects) {
        if (del6) {
          GetGame().ObjectDelete(del6);
        }
      }
      debugObjects.Clear();
    }

    LogThis(logPrefix + "deleteTrigger: END");
  }

  bool isTriggerDisabled() {
    return isDisabled;
  }

  bool IsCanBeTriggered() {
    // Если триггер закончил свою работу
    if (isDisabled) {
      return false;
    }

    float currentTime = GetGameTime();

    LogThis(logPrefix + "nextTriggerTime: " + nextTriggerTime);
    LogThis(logPrefix + "currentTime: " + currentTime);

    // Вычисляем не прошёл ли кулдаун
    if (nextTriggerTime > 0 && currentTime > nextTriggerTime) {
      return true;
    }

    return false;
  }

  /**
   * Return seconds from server start
   */
  float GetGameTime() { return GetGame().GetTickTime(); };

  bool IsNoDependencies() {
    if (triggerDependencies.Count() > 0) {
      int totalTriggered = 0;
      foreach (int dependId : triggerDependencies) {
        LogThis(logPrefix + "Depends on pointId: " + dependId);

        ref MPG_Trigger depTrigger = GetTrigger(dependId);

        if (depTrigger) {
          if (depTrigger.GetIsTriggered()) {
            // Если нам нужен любой сработавший триггер, то сразу возвращаем true
            if (triggerDependenciesAnyOf) {
              return true;
            }

            totalTriggered++;
          }
        }
      }

      // Возвращаем true, если количество сработавших триггеров равно общему количеству зависимостей.
      return totalTriggered == triggerDependencies.Count();
    } else {
      return true;
    }
  }

  MPG_Trigger GetTrigger(int m_pointId) {
    array<MPG_Trigger> triggers = MPG_Spawner.GetInstance().GetTriggers();

    foreach (ref MPG_Trigger m_curTrigger : triggers) {
      if (m_curTrigger.GetPointId() == m_pointId) {
        return m_curTrigger;
      }
    }

    return null;
  }

  // clang-format off
  protected bool IsRealAlivePlayer(Object object) {
    // clang-format on
    PlayerBase player = PlayerBase.Cast(object);
    if (!player) {
      return false;
    }

    if (!player.GetIdentity()) {
      return false;
    }

    if (player.IsAlive() && player.GetIdentity().GetPlainId()) {
      return true;
    }

    return false;
  }

  override bool CanAddObjectAsInsider(Object object) {
    return IsRealAlivePlayer(object);
  }

  // Удаляем игрока из инсайдеров триггера, если он откис, что бы не дрочить триггер и не вызывать ошибок.
  override protected bool ShouldRemoveInsider(TriggerInsider insider) {
    return !IsRealAlivePlayer(insider.GetObject());
  }

  override protected void OnEnterServerEvent(TriggerInsider insider) {

    // Добавил isDisabled по многочисленным просьбам
    // т.к. нотификация входа часто используется для игровой логики.
    if (notificationTextEnter != "" && !isDisabled) {
      NotificationSystem.SendNotificationToPlayerExtended(Man.Cast(insider.GetObject()), notificationTime, notificationTitle, notificationTextEnter, notificationIcon);
    }

    TryToProcessMappingDataObjects(MPG_TriggerEventType.ENTER);
    TryToEnableTriggers(MPG_TriggerEventType.ENTER);

    if (triggerEnterDelay == 0) {
      TryToSpawn(insider, true);
    }
  }

  override void EOnLeave(IEntity other, int extra) {
    super.EOnLeave(other, extra);

    if (!isDisabled) {
      // Реагируем только на игроков
      PlayerBase player = PlayerBase.Cast(other);
      if (player) {
        if (notificationTextExit != "" && !isDisabled) {
          NotificationSystem.SendNotificationToPlayerExtended(player, notificationTime, notificationTitle, notificationTextExit, notificationIcon);
        }

        isEntered = GetInsiders().Count() > 0;

        if (triggerCleanupDelay > 0 && triggerCleanupOnLeave) {
          // Пробуем зачистить живность при выходе из триггера
          GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(TryToCleanup, triggerCleanupDelay * 1000, false);
        }

        if (player.GetIdentity()) {
          Logger.Log(logPrefix + "ExitTime: " + GetGameTime() + "; " + Logger.GetPlayerInfo(player));
        }

        // Сначала пробуем включить другие триггеры
        TryToEnableTriggers(MPG_TriggerEventType.LEAVE);
        // А уже после этого пробуем выключить сам текущий триггер
        TryToDisable(MPG_TriggerEventType.LEAVE);
      }
    }
  }

  override protected void OnStayServerEvent(TriggerInsider insider, float deltaTime) {
    super.OnStayServerEvent(insider, deltaTime);

    // Работаем только с активным триггером. Выключенный триггер нас не интересует.
    if (!isDisabled) {
      // Если ещё не было попытки спавна, пробуем подсчитать задержку и потом спавн
      if (!isEntered) {
        if (triggerEnterDelay > 0 && GetGameTime() > insider.timeEntered + triggerEnterDelay) {
          TryToSpawn(insider, true);
        }
      } else {
        // Т.к. делать дорогие проверки часто, не очень хорошо, будет удорожать их по мере необходимости
        if (spawnLoopInside) {
          // Если включен циклический спавн, то будем считать количество инсайдеров
          // TODO Возможно тут лучше использовать insider.GetObject() ?
          if (GetInsiders().Count()) {
            // Если кто-то есть внутри и время следующего спавна уже наступило, будем пытаться спавнить.
            if (GetGameTime() > nextTriggerTime) {
              LogThis(logPrefix + "Will TryToSpawn without leaving; insiders: " + GetInsiders().Count());
              // TODO Проверить работоспособность при ситуации, когда проверки внутри TryToSpawn не проходят
              //  это может оказаться достаточно дорогой операцией т.к. дрочить TryToSpawn достаточно дорого
              //  особенно IsNoDependencies
              TryToSpawn(insider, false);
            }
          }
        }
      }

      if (triggerCleanupOnLunchTime) {
        if (triggerCleanupDelay > 0) {
          if (!IsWorkingTime()) {
            // Пробуем зачистить живность если время работы триггера не наступило
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(TryToCleanup, triggerCleanupDelay * 1000, false);
          }
        }
      }
    }
  }

  void TryToSpawn(TriggerInsider insider, bool isEnterEvent) {
    // Если триггер выключен нет смысла его напрягать попытками спавна
    if (isDisabled) {
      LogThis(logPrefix + "Will NOT TryToSpawn, trigger is Disabled");

      return;
    }

    if (insider.GetObject() && IsWorkingTime() && IsNoDependencies()) {
      if (IsRealAlivePlayer(insider.GetObject())) {
        string playerInfo = Logger.GetPlayerInfo(PlayerBase.Cast(insider.GetObject()));
        if (isEnterEvent) {
          isEntered = true;
          Logger.Log(logPrefix + "EnterTime: " + GetGameTime() + "; " + playerInfo);
        } else {
          LogThis(logPrefix + "StayInTime: " + GetGameTime() + "; " + playerInfo);
        }

        if (IsCanBeTriggered()) {
          LogThis(logPrefix + "Will GoSpawn");

          SetNextTriggerTime(GetRandInt(triggerCooldown));
          GoSpawn(insider, isEnterEvent);

        } else {
          LogThis(logPrefix + "Will NOT GoSpawn");
        }
      } else {
        LogThis(logPrefix + "Will NOT TryToSpawn, it is not alive player");
      }
    }
  }

  void GoSpawn(TriggerInsider insider, bool isEnterEvent) {

    isTriggered = true;

    vector spawnpos;
    float spawnchance, rndflt;
    int rndnum;
    int j = 0;
    int createdCount = 0;
    int tryingCount = 0;
    bool shouldRotate;
    bool shouldSpawn = true;
    string posrot, pos, ori, classNameToSpawn;
    TStringArray loc, spawnItemArr;

    int randSpawnLimit = Math.RandomIntInclusive(spawnMin, spawnMax);

    int countToCreate = randSpawnLimit;

    int totalSpawnedCount = GetSpawnedCount();

    LogThis(logPrefix + "spawnMin: " + spawnMin + "; spawnMax: " + spawnMax);
    LogThis(logPrefix + "randSpawnLimit: " + countToCreate + "; GetSpawnedCount: " + totalSpawnedCount);
    LogThis(logPrefix + "countToCreate: " + countToCreate);

    if (spawnCountLimit > 0 && (totalSpawnedCount + countToCreate) >= spawnCountLimit) {
      countToCreate = spawnCountLimit - totalSpawnedCount;
      LogThis(logPrefix + "countToCreate: " + countToCreate + "; override by: spawnCountLimit ends;");
    }

    if (countToCreate < 0) {
      countToCreate = 0;
      LogThis(logPrefix + "countToCreate: " + countToCreate + "; override by: countToCreate < 0;");
    }

    if (countToCreate) {
      TryToProcessMappingDataObjects(MPG_TriggerEventType.FIRST_SPAWN);
      TryToEnableTriggers(MPG_TriggerEventType.FIRST_SPAWN);

      vector pPosition;

      bool shouldCalcDistance = isEnterEvent && triggerSafeDistance > 0 && spawnRadius > 0 && spawnRadius + 1 > triggerSafeDistance;

      if (shouldCalcDistance) {
        PlayerBase player = PlayerBase.Cast(insider.GetObject());
        if (player) {
          pPosition = player.GetPosition();
        }
      }

      TStringArray positions = new TStringArray();

      if (countToCreate < spawnPositions.Count()) {
        positions.Copy(spawnPositions);

        float spawnDistance;

        LogThis(logPrefix + "countToCreate < spawnPositions");

        while (true) {
          rndnum = Math.RandomIntInclusive(0, positions.Count() - 1);

          shouldRotate = false;
          pos = positions.Get(rndnum);

          ori = "0 0 0";
          if (positions.Get(rndnum).Contains("|")) {
            posrot = positions.Get(rndnum);
            loc = new TStringArray;
            posrot.Split("|", loc);
            pos = loc[0];
            ori = loc[1];
            shouldRotate = true;
          }

          // Заменим запятые на пробелы и двойные пробелы на одинарные,
          // что бы избегать ошибок при спавне и неправильном написании координат
          // TODO Реализовать конвертацию в нужный формат при загрузке конфигов с последующим сохранением.
          pos.Replace(",", " ");
          pos.Replace("  ", " ");
          ori.Replace(",", " ");
          ori.Replace("  ", " ");

          spawnpos = pos.ToVector();

          if (spawnRadius > 0) {
            spawnpos = SetRandomPos(spawnpos, spawnRadius);
          }

          classNameToSpawn = spawnList.GetRandomElement();
          classNameToSpawn.Replace(" ", "");
          spawnchance = 1.0;
          spawnItemArr = new TStringArray;
          if (classNameToSpawn.Contains("|")) {
            classNameToSpawn.Split("|", spawnItemArr);
            classNameToSpawn = spawnItemArr[0];
            spawnchance = spawnItemArr[1].ToFloat();
          } else {
            spawnItemArr.Insert(classNameToSpawn);
          }

          rndflt = Math.RandomFloatInclusive(0, 1.0);
          shouldSpawn = true;

          if (shouldCalcDistance) {
            spawnDistance = vector.Distance(pPosition, spawnpos);
            if (triggerSafeDistance > spawnDistance) {
              shouldSpawn = false;
            }
          }

          if (spawnchance >= rndflt && shouldSpawn) {
            auto object1 = MPG_Spawner_CreateObject(spawnItemArr, spawnpos);
            if (shouldRotate) {
              object1.SetOrientation(ori.ToVector());
            }
            positions.RemoveOrdered(rndnum);
            createdCount++;
          }

          tryingCount++;

          if (countToCreate == createdCount) {
            break;
          }
        }

      } else {
        LogThis(logPrefix + "countToCreate > spawnPositions");

        while (true) {
          shouldRotate = false;
          pos = spawnPositions.Get(j);

          ori = "0 0 0";
          if (spawnPositions.Get(j).Contains("|")) {
            posrot = spawnPositions.Get(j);
            loc = new TStringArray;
            posrot.Split("|", loc);
            pos = loc[0];
            ori = loc[1];
            shouldRotate = true;
          }

          // Заменим запятые на пробелы и двойные пробелы на одинарные,
          // что бы избегать ошибок при спавне и неправильном написании координат
          // TODO Реализовать конвертацию в нужный формат при загрузке конфигов с последующим сохранением.
          pos.Replace(",", " ");
          pos.Replace("  ", " ");
          ori.Replace(",", " ");
          ori.Replace("  ", " ");

          spawnpos = pos.ToVector();
          if (spawnRadius > 0) {
            spawnpos = SetRandomPos(spawnpos, spawnRadius);
          }

          classNameToSpawn = spawnList.GetRandomElement();
          classNameToSpawn.Replace(" ", "");
          spawnchance = 1.0;
          spawnItemArr = new TStringArray;
          if (classNameToSpawn.Contains("|")) {
            classNameToSpawn.Split("|", spawnItemArr);
            classNameToSpawn = spawnItemArr[0];
            spawnchance = spawnItemArr[1].ToFloat();
          } else {
            spawnItemArr.Insert(classNameToSpawn);
          }

          rndflt = Math.RandomFloatInclusive(0, 1.0);
          shouldSpawn = true;

          if (shouldCalcDistance) {
            spawnDistance = vector.Distance(pPosition, spawnpos);
            if (triggerSafeDistance > spawnDistance) {
              shouldSpawn = false;
            }
          }

          if (spawnchance >= rndflt && shouldSpawn) {
            auto object2 = MPG_Spawner_CreateObject(spawnItemArr, spawnpos);
            if (shouldRotate) {
              object2.SetOrientation(ori.ToVector());
            }
            j++;
            createdCount++;
            if (j == spawnPositions.Count()) {
              j = 0;
            }
          }

          tryingCount++;

          if (countToCreate == createdCount) {
            break;
          }
        }
      }
    }

    if (notificationTextSpawn != "" && createdCount > 0) {
      string textToDisplay = GetDeclensionText(countToCreate, notificationTextSpawn);

      for (int iplr = 0; iplr < GetInsiders().Count(); iplr++) {
        Man notifyPlayer = Man.Cast(GetInsiders().Get(iplr).GetObject());
        if (notifyPlayer) {
          NotificationSystem.SendNotificationToPlayerExtended(notifyPlayer, notificationTime, notificationTitle, textToDisplay, notificationIcon);
        }
      }
    }

    // Эти логи помогают определить насколько сложно разместить живность в данном триггере
    Logger.Log(logPrefix + "tryingCount: " + tryingCount);
    Logger.Log(logPrefix + "createdCount: " + createdCount);
  }

  /**
   * Пробуем удалить живность, которая заспавнилась
   */
  void TryToCleanup() {
    // Тут обязательно нужно делать дополнительные проверки
    // т.к. на момент выполнения функции из-за задержки таймеров, те проверки,
    // которые были перед выполнением этой функции могут оказаться ошибочными
    if (creaturesToCleanup.Count()) {
      if ((triggerCleanupOnLeave && !GetInsiders().Count()) || (triggerCleanupOnLunchTime && !IsWorkingTime())) {
        LogThis(logPrefix + "TryToCleanupCreatures: yes; count: " + creaturesToCleanup.Count());

        foreach (Object creatureToCleanup : creaturesToCleanup) {
          if (creatureToCleanup) {
            // При иммерсивной очистке сначала ставим нулевое здоровье, что бы добиться эффекта смерти животных и зомби
            if (triggerCleanupImmersive) {
              creatureToCleanup.SetHealth("", "", 0.0);
              GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, 2000, false, creatureToCleanup);
            } else {
              GetGame().ObjectDelete(creatureToCleanup);
            }
          }
        }
        creaturesToCleanup.Clear();
      } else {
        LogThis(logPrefix + "TryToCleanupCreatures: none; insidersCount: " + GetInsiders().Count() + "; IsWorkingTime: " + IsWorkingTime());
      }
    } else {
      LogThis(logPrefix + "TryToCleanupCreatures: none; creaturesToCleanup: " + creaturesToCleanup.Count());
    }

    if (lootToCleanup.Count()) {
      if ((triggerCleanupOnLeave && !GetInsiders().Count()) || (triggerCleanupOnLunchTime && !IsWorkingTime())) {
        LogThis(logPrefix + "TryToCleanupLoot: yes; count: " + lootToCleanup.Count());

        foreach (Object itemToCleanup : lootToCleanup) {
          ItemBase iToCleanup = ItemBase.Cast(itemToCleanup);

          if (iToCleanup && iToCleanup.GetHierarchyRootPlayer() == null) {
            // Безопасно удаляем предмет (может быть так, что его возьмут из места за пределами зоны действия триггера)
            // TODO Сделать пометку на запрет удаления или просто удаление из списка на удаление
            iToCleanup.DeleteSafe();
          }
        }
        lootToCleanup.Clear();
      } else {
        LogThis(logPrefix + "TryToCleanupLoot: none; insidersCount: " + GetInsiders().Count() + "; IsWorkingTime: " + IsWorkingTime());
      }
    } else {
      LogThis(logPrefix + "TryToCleanupLoot: none; lootToCleanup: " + lootToCleanup.Count());
    }

    /**
     * В любом случае необходимо почистить список,
     * на основе которого считаются лимиты спавна и выигрыш.
     * Иначе ломается логика спавна.
     */
    CleanSpawnedInstances();
  }

  /**
   * Парсим сообщение, что бы можно было склонять слова
   */
  string GetDeclensionText(int count, string message) {
    string textToDisplay = message;

    if (message.Contains(";")) {
      string s0, s2, s3, s4, s5;
      TStringArray part = new TStringArray;

      notificationTextSpawn.Split(";", part);
      s0 = part[0];
      int s1 = count;

      if (part[1]) {
        s2 = Declension(count, part[1]);
      }

      if (part[2]) {
        s3 = Declension(count, part[2]);
      }

      if (part[3]) {
        s4 = Declension(count, part[3]);
      }

      if (part[4]) {
        s5 = Declension(count, part[4]);
      }

      textToDisplay = string.Format(s0, s1, s2, s3, s4, s5);
    }

    return textToDisplay;
  }

  int GetSpawnedCount() {
    int allCount = 0;

    TIntArray spCreatures = MPG_Spawner.GetInstance().GetSpawnedCreatures(GetPointId());
    if (spCreatures) {
      LogThis(logPrefix + "AlreadySpawned Creatures: " + spCreatures.Count());
      allCount += spCreatures.Count();
    }
    TIntArray spLoot = MPG_Spawner.GetInstance().GetSpawnedLoot(GetPointId());
    if (spLoot) {
      LogThis(logPrefix + "AlreadySpawned Loot: " + spLoot.Count());
      allCount += spLoot.Count();
    }

    return allCount;
  }

  void CleanSpawnedInstances() {
    TIntArray spawnedCreatures = MPG_Spawner.GetInstance().GetSpawnedCreatures(GetPointId());
    if (spawnedCreatures) {
      LogThis(logPrefix + "CleanSpawnedCreaturesCount: " + spawnedCreatures.Count());
      spawnedCreatures.Clear();
    }

    TIntArray spawnedLoot = MPG_Spawner.GetInstance().GetSpawnedLoot(GetPointId());
    if (spawnedLoot) {
      LogThis(logPrefix + "CleanSpawnedLootCount: " + spawnedLoot.Count());
      spawnedLoot.Clear();
    }
  }

  Object MPG_Spawner_CreateObject(TStringArray itemArr, vector pos) {
    int flags = ECE_OBJECT_SWAP | ECE_INITAI;

    if (pos[1] == 0) {
      flags = ECE_PLACE_ON_SURFACE | ECE_INITAI;
    }

    auto newObject = GetGame().CreateObjectEx(itemArr[0], pos, flags);

    if (newObject) {
      LogThis(logPrefix + "Spawned: " + newObject + "; Pos: " + pos.ToString());
    } else {
      Logger.Log(logPrefix + "ERROR: Object '" + itemArr[0] + "' is NOT created");

      return newObject;
    }

    // Для всех настроек, кроме лайвтайма, параметры следующие:
    // -3 - отключено, будет применено дефолтное, для предмета значение.
    // -2 - полный рандом (от 0 до 100%). Для стадий еды это три состояния Гнилое, Сушеное, Сырое. Для всего остального процент от 100%-го значения.
    // -1 - максимальное значение (для состояния еды - сырое, для всего остального 100% значения).
    // 0-100 - числа, между которыми будет выбран рандом. от нуля до 100%.

    // Принцип установки параметров:
    // "Класснейм|шанс спавна|лайвтайм|кол-во|здоровье|стадия еды"

    int lifeTime = 0;
    string quantity = "-3";
    string health = "-3";
    string stage = "-3";

    if (itemArr[2]) {
      lifeTime = itemArr[2].ToInt();
    }
    if (itemArr[3]) {
      quantity = itemArr[3];
    }
    if (itemArr[4]) {
      health = itemArr[4];
    }
    if (itemArr[5]) {
      stage = itemArr[5];
    }

    // Устанавливаем здоровье (актуально для всего, что спавнится)
    if (health != "-3") {
      int minHealth = 0;
      int maxHealth = newObject.GetMaxHealth("", "");

      // Тут кейс для '-1' - полное количество.
      int setHealth = maxHealth;

      if (health == "-2") {
        // Если '-2', значит ставим рандом от нуля, до максимума
        setHealth = Math.RandomIntInclusive(minHealth, maxHealth);
      } else {
        if (health != "-1") {
          // Если не '-1', то пытаемся назначить рандомное количество из заданного диапазона.
          TStringArray minMaxH = new TStringArray;
          health.Split("-", minMaxH);
          float mnH = maxHealth / 100 * minMaxH[0].ToFloat();
          float mxH = maxHealth / 100 * minMaxH[1].ToFloat();

          mnH = Math.Floor(mnH);
          mxH = Math.Round(mxH);

          if (mnH < 1) {
            mnH = 1;
          }
          if (mxH > maxHealth) {
            mxH = maxHealth;
          }

          setHealth = Math.RandomIntInclusive(mnH, mxH);
        }
      }

      newObject.SetHealth("", "", setHealth);

      LogThis(logPrefix + "SetHealth: " + setHealth + "/" + maxHealth);
    }

    AnimalBase animal = AnimalBase.Cast(newObject);
    ZombieBase zombie = ZombieBase.Cast(newObject);

    if (animal) {
      animal.SetMPG_Spawner_Flag();
      animal.SetMPG_SPWNR_PointId(GetPointId());

      if (clearDeathAnimals) {
        animal.SetMPG_SPWNR_Timer(clearDeathAnimals);
      }

      if (spawnCountLimit) {
        MPG_Spawner.GetInstance().AddSpawnedInstance(GetPointId(), animal.GetID());
      }

      if (triggerCleanupDelay > 0) {
        creaturesToCleanup.Insert(animal);
      }

      // Устанавливаем лайвтайм, если он больше нуля
      if (lifeTime > 0) {
        animal.SetLifetime(lifeTime);
      }
    }

    if (zombie) {
      zombie.SetMPG_Spawner_Flag();
      zombie.SetMPG_SPWNR_PointId(GetPointId());

      if (clearDeathZombies) {
        zombie.SetMPG_SPWNR_Timer(clearDeathZombies);
      }

      if (spawnCountLimit) {
        MPG_Spawner.GetInstance().AddSpawnedInstance(GetPointId(), zombie.GetID());
      }

      if (triggerCleanupDelay > 0) {
        creaturesToCleanup.Insert(zombie);
      }

      // Устанавливаем лайвтайм, если он больше нуля
      if (lifeTime > 0) {
        zombie.SetLifetime(lifeTime);
      }
    }

    if (!animal && !zombie) {
      // Если это не зомби и не живность, значит это лут, будем спавнить лут
      ItemBase item = ItemBase.Cast(newObject);

      if (item) {

        if (spawnCountLimit) {
          MPG_Spawner.GetInstance().AddSpawnedLoot(GetPointId(), item.GetID());
        }

        if (triggerCleanupDelay > 0) {
          lootToCleanup.Insert(item);
        }

        // Устанавливаем лайвтайм, если он больше нуля
        if (lifeTime > 0) {
          item.SetLifetime(lifeTime);
        }

        // Устанавливаем количество
        if (quantity != "-3") {
          // Проверка на магазин
          bool isMag = item.IsMagazine();

          int minQuantity = 0;
          int maxQuantity = item.GetQuantityMax();

          if (isMag) {
            // Для магазина максимальное количество надо получать чуть иначе
            maxQuantity = Magazine.Cast(item).GetAmmoMax();
          }

          // Тут кейс для '-1' - полное количество.
          int setQuantity = maxQuantity;

          if (quantity == "-2") {
            // Если '-2', значит ставим рандом от нуля, до максимума
            setQuantity = Math.RandomIntInclusive(minQuantity, maxQuantity);
          } else {
            if (quantity != "-1") {
              // Если не '-1', то пытаемся назначить рандомное количество из заданного диапазона.
              TStringArray minMaxQ = new TStringArray;
              quantity.Split("-", minMaxQ);
              float mnQ = (maxQuantity / 100) * minMaxQ[0].ToFloat();
              float mxQ = (maxQuantity / 100) * minMaxQ[1].ToFloat();

              mnQ = Math.Floor(mnQ);
              mxQ = Math.Round(mxQ);

              if (mnQ < 1) {
                mnQ = 1;
              }

              if (mxQ > maxQuantity) {
                mxQ = maxQuantity;
              }

              setQuantity = Math.RandomIntInclusive(mnQ, mxQ);
            }
          }

          if (isMag) {
            Magazine itemMag = Magazine.Cast(item);
            itemMag.ServerSetAmmoCount(setQuantity);
          } else {
            item.SetQuantity(setQuantity);
          }

          LogThis(logPrefix + "SetQuantity: " + setQuantity + "/" + maxQuantity);
        }

        if (item.HasFoodStage() && stage != "-3") {

          Edible_Base food = Edible_Base.Cast(newObject);

          // Тут кейс для '-1' - сырое.
          int foodStage = FoodStageType.RAW;

          if (stage == "-2") {
            int r03 = Math.RandomIntInclusive(1, 3);

            switch (r03) {
            case 1:
              foodStage = FoodStageType.RAW;
              break;

            case 2:
              foodStage = FoodStageType.DRIED;
              break;

            case 3:
              foodStage = FoodStageType.ROTTEN;
              break;
            }
          } else {
            if (stage != "-1") {
              // Если не '-1', то пытаемся назначить рандомное количество из заданного диапазона.
              TStringArray minMaxS = new TStringArray;
              stage.Split("-", minMaxS);

              int rStage = Math.RandomIntInclusive(minMaxS[0].ToInt(), minMaxS[1].ToInt());

              if (rStage <= 66) {
                foodStage = FoodStageType.DRIED;
              }
              if (rStage <= 33) {
                foodStage = FoodStageType.ROTTEN;
              }
              if (rStage > 66) {
                foodStage = FoodStageType.RAW;
              }
            }
          }

          LogThis(logPrefix + "foodStage: " + foodStage);

          food.ChangeFoodStage(foodStage);
        }
      }
    }

    return newObject;
  }

  vector SetRandomPos(vector position, float radius) {
    vector randompos;
    float t, u, v, w, x, y;

    u = Math.RandomFloatInclusive(0.0, 1.0);
    v = Math.RandomFloatInclusive(0.0, 1.0);

    w = radius * Math.Sqrt(u);
    t = 2 * Math.PI * v;
    x = w * Math.Cos(t);
    y = w * Math.Sin(t);

    randompos[0] = position[0] + x;
    randompos[1] = position[1];
    randompos[2] = position[2] + y;
    // check surface
    //    if (GetGame().SurfaceY(randompos[0], randompos[2]) > position[1]) {
    //      randompos[1] = GetGame().SurfaceY(randompos[0], randompos[2]) + 0.3;
    //    }

    return randompos;
  }

  bool IsWorkingTime() {
    int pass, hour;
    int wtbegin = 0;
    int wtend = 24;
    if (triggerWorkingTime.Contains("-")) {
      TStringArray times = new TStringArray;
      triggerWorkingTime.Split("-", times);
      wtbegin = times[0].ToInt();
      wtend = times[1].ToInt();
    }

    // Нам нужны только часы
    GetGame().GetWorld().GetDate(pass, pass, pass, hour, pass);
    if (wtbegin > wtend) {
      if (hour >= wtbegin || hour <= wtend) {
        return true;
      }
      return false;
    } else if (wtbegin < wtend) {
      if (hour >= wtbegin && hour <= wtend) {
        return true;
      }
      return false;
    } else {
      return false;
    }
  }

  /**
   * Вместо поворота вокруг точки используем движение по вектору
   * т.к. повороты вокруг точки в дейзе работают через жопу
   * (ну или я так и не смог понять как их правильно готовить)
   */
  vector GetSquareWallCoords(vector dbgPos, float distance, float angle) {
    angle = Math.NormalizeAngle(angle);

    float rad = (Math.NormalizeAngle(angle) * Math.DEG2RAD) + Math.PI;

    float newX = dbgPos[0] + Math.Sin(rad) * distance;
    float newY = dbgPos[2] + Math.Cos(rad) * distance;

    return Vector(newX, dbgPos[1], newY);
  }

  void DrawDebugShape() {
    // Спавним визуализацию только если установлен мод на визуализацию
#ifdef MPG_SPAWN_ZONE
    if (showVisualisation) {
      string shapeColor = "blue";

      if (triggerDebugColor) {
        shapeColor = triggerDebugColor;
      }

      float scaleRadius = triggerRadiusRand / 10;
      Param1<float> p_scaleRadius = new Param1<float>(scaleRadius);

      // Проверка инициализации debugPos
      if (debugPos == vector.Zero) {
        LogThis(logPrefix + "ERROR: debugPos is not initialized");
        return;
      }

      switch (GetTriggerShape()) {
      case TriggerShape.BOX:
        // Нижняя грань
        Object debugSqBot = GetGame().CreateObjectEx("MPG_Spawner_Debug_Square_" + shapeColor, debugPos, ECE_NONE);
        // Верхняя грань
        Object debugSqTop = GetGame().CreateObjectEx("MPG_Spawner_Debug_Square_" + shapeColor, debugPos + Vector(0, triggerHeightRand, 0), ECE_NONE);

        float halfHeight = triggerHeightRand / 2;
        float halfWX = triggerWidthXRand * 0.5;
        float halfWY = triggerWidthYRand * 0.5;

        // Боковая грань X1 - левая
        Object debugSqX1 = GetGame().CreateObjectEx("MPG_Spawner_Debug_Square_1_" + shapeColor, debugPos, ECE_NONE);
        // Боковая грань X2 - правая
        Object debugSqX2 = GetGame().CreateObjectEx("MPG_Spawner_Debug_Square_1_" + shapeColor, debugPos, ECE_NONE);

        // Боковая грань Y1 - передняя
        Object debugSqY1 = GetGame().CreateObjectEx("MPG_Spawner_Debug_Square_1_" + shapeColor, debugPos, ECE_NONE);
        // Боковая грань Y2 - задняя
        Object debugSqY2 = GetGame().CreateObjectEx("MPG_Spawner_Debug_Square_1_" + shapeColor, debugPos, ECE_NONE);

        // Проверка, что объект был создан
        if (!debugSqBot) {
          LogThis(logPrefix + "ERROR: Debug Box debugSqBot NOT Created");
        }
        if (!debugSqTop) {
          LogThis(logPrefix + "ERROR: Debug Box debugSqTop NOT Created");
        }
        if (!debugSqX1) {
          LogThis(logPrefix + "ERROR: Debug Box debugSqX1 NOT Created");
        }
        if (!debugSqY1) {
          LogThis(logPrefix + "ERROR: Debug Box debugSqY1 NOT Created");
        }
        if (!debugSqX2) {
          LogThis(logPrefix + "ERROR: Debug Box debugSqX2 NOT Created");
        }
        if (!debugSqY2) {
          LogThis(logPrefix + "ERROR: Debug Box debugSqY2 NOT Created");
        }

        if (!debugSqBot || !debugSqTop || !debugSqX1 || !debugSqY1 || !debugSqX2 || !debugSqY2) {
          return;
        }

        debugObjects.Insert(debugSqBot);
        debugObjects.Insert(debugSqTop);
        debugObjects.Insert(debugSqX1);
        debugObjects.Insert(debugSqY1);
        debugObjects.Insert(debugSqX2);
        debugObjects.Insert(debugSqY2);

        // Размер квадратов 20x20м поэтому масштабируем с делением на 20
        float scaleHorizontal = Math.Max(triggerWidthXRand, triggerWidthYRand) / 20;
        float scaleX = Math.Max(triggerWidthYRand, triggerHeightRand * 2) / 20;
        float scaleY = Math.Max(triggerHeightRand * 2, triggerWidthXRand) / 20;

        vector triggerOri = GetOrientation();
        float xOri = triggerOri[0];
        float xOri1 = Math.NormalizeAngle(xOri + 90);

        vector rotateX = Vector(xOri, 0, 0);
        vector rotateY = Vector(xOri1, 0, 0);

        debugSqBot.SetOrientation(rotateX);
        debugSqTop.SetOrientation(rotateX);

        debugSqX1.SetOrientation(rotateX);
        debugSqY1.SetOrientation(rotateY);

        debugSqX2.SetOrientation(rotateX);
        debugSqY2.SetOrientation(rotateY);

        debugSqX1.SetPosition(GetSquareWallCoords(debugPos, halfWX, xOri1));
        debugSqX2.SetPosition(GetSquareWallCoords(debugPos, halfWX, xOri1 + 180));

        debugSqY1.SetPosition(GetSquareWallCoords(debugPos, halfWY, xOri));
        debugSqY2.SetPosition(GetSquareWallCoords(debugPos, halfWY, xOri + 180));

        debugSqBot.SetScale(scaleHorizontal);
        debugSqTop.SetScale(scaleHorizontal);

        debugSqX1.SetScale(scaleX);
        debugSqX2.SetScale(scaleX);

        debugSqY1.SetScale(scaleY);
        debugSqY2.SetScale(scaleY);

        Param1<float> p_scaleHorizontal = new Param1<float>(scaleHorizontal);
        debugSqBot.RPCSingleParam(-128965, p_scaleHorizontal, true);
        debugSqTop.RPCSingleParam(-128965, p_scaleHorizontal, true);

        Param1<float> p_scaleX = new Param1<float>(scaleX);
        debugSqX1.RPCSingleParam(-128965, p_scaleX, true);
        debugSqX2.RPCSingleParam(-128965, p_scaleX, true);

        Param1<float> p_scaleY = new Param1<float>(scaleY);
        debugSqY1.RPCSingleParam(-128965, p_scaleY, true);
        debugSqY2.RPCSingleParam(-128965, p_scaleY, true);

        LogThis(logPrefix + "Trigger: Debug Box Created;");

        break;
      case TriggerShape.CYLINDER:
        // Создаём цилиндр без крыши и пола
        Object debugCylWall = GetGame().CreateObjectEx("MPG_Spawner_Debug_Cylinder_1_" + shapeColor, debugPos, ECE_NONE);
        // Создаём пол на позиции нижней границы цилиндра
        Object debugCircleBottom = GetGame().CreateObjectEx("MPG_Spawner_Debug_Circle_" + shapeColor, debugPos, ECE_NONE);
        // Создаём крышу на позиции верхней гранимцы цилиндра
        Object debugCircleTop = GetGame().CreateObjectEx("MPG_Spawner_Debug_Circle_" + shapeColor, debugPos + Vector(0, triggerHeightRand, 0), ECE_NONE);

        // Проверка, что все три объекта были созданы
        if (!debugCylWall || !debugCircleBottom || !debugCircleTop) {
          LogThis(logPrefix + "ERROR: Debug Cylinder NOT Created");
          return;
        }

        debugObjects.Insert(debugCylWall);
        debugObjects.Insert(debugCircleBottom);
        debugObjects.Insert(debugCircleTop);

        debugCylWall.SetScale(scaleRadius);
        debugCylWall.RPCSingleParam(-128965, p_scaleRadius, true);

        // Сделаем крышу и пол цилиндра немного больше,
        // что бы они визуально выпирали за границы цилиндра.
        // Таким образом визуализация будет чутка лучше.
        debugCircleBottom.SetScale(scaleRadius * 1.02);
        debugCircleTop.SetScale(scaleRadius * 1.02);

        Param1<float> p_scaleRadius1 = new Param1<float>(scaleRadius * 1.02);
        debugCircleBottom.RPCSingleParam(-128965, p_scaleRadius1, true);
        debugCircleTop.RPCSingleParam(-128965, p_scaleRadius1, true);

        LogThis(logPrefix + "Trigger: Debug Cylinder Created;");
        break;
      case TriggerShape.SPHERE:
        Object debugSphere = GetGame().CreateObjectEx("MPG_Spawner_Debug_Sphere_" + shapeColor, debugPos, ECE_NONE);
        // Проверка, что объект был создан
        if (!debugSphere) {
          LogThis(logPrefix + "ERROR: Debug Sphere NOT Created");
          return;
        }

        debugObjects.Insert(debugSphere);

        debugSphere.SetScale(scaleRadius);
        debugSphere.RPCSingleParam(-128965, p_scaleRadius, true);

        LogThis(logPrefix + "Trigger: Debug Sphere Created;");
        break;
      default:
        LogThis(logPrefix + "Trigger: Shape is incorrect;");
        break;
      }
    }
#endif
  }

  /**
   * Пробуем активировать другие триггеры
   */
  void TryToEnableTriggers(MPG_TriggerEventType eventType) {
    switch (eventType) {
    case MPG_TriggerEventType.ENTER:
      // Если триггер выключен, нельзя включить другие триггеры
      if (isDisabled) {
        LogThis(logPrefix + "TryToEnableTriggers: ENTER Trigger is Disabled");

        return;
      }

      if (triggersToEnableOnEnter.Count()) {
        foreach (int actOnEnter : triggersToEnableOnEnter) {
          MPG_Trigger actOnEnterTrigger = GetTrigger(actOnEnter);
          if (actOnEnterTrigger) {
            actOnEnterTrigger.SetEnabled();
          }
        }
        LogThis(logPrefix + "TryToEnableTriggersOn: ENTER");
      }
      break;

    case MPG_TriggerEventType.FIRST_SPAWN:
      // Если триггер выключен, нельзя включить другие триггеры
      if (isDisabled) {
        LogThis(logPrefix + "TryToEnableTriggers: FIRST_SPAWN Trigger is Disabled");

        return;
      }

      if (triggersToEnableOnFirstSpawn.Count()) {
        foreach (int actOnFSpawn : triggersToEnableOnFirstSpawn) {
          MPG_Trigger actOnFSpawnTrigger = GetTrigger(actOnFSpawn);
          if (actOnFSpawnTrigger) {
            actOnFSpawnTrigger.SetEnabled();
          }
        }
        LogThis(logPrefix + "TryToEnableTriggersOn: FIRST_SPAWN");
      }
      break;

    case MPG_TriggerEventType.WIN:
      // Тут не нужно проверять на выключенность триггера т.к. он не включит то, что должен включать.
      if (triggersToEnableOnWin.Count()) {
        foreach (int actOnWin : triggersToEnableOnWin) {
          MPG_Trigger actOnWinTrigger = GetTrigger(actOnWin);
          if (actOnWinTrigger) {
            actOnWinTrigger.SetEnabled();
          }
        }
        LogThis(logPrefix + "TryToEnableTriggersOn: WIN");
      }
      break;

    case MPG_TriggerEventType.LEAVE:
      if (triggersToEnableOnLeave.Count()) {
        foreach (int actOnLeave : triggersToEnableOnLeave) {
          MPG_Trigger actOnLeaveTrigger = GetTrigger(actOnLeave);
          if (actOnLeaveTrigger) {
            actOnLeaveTrigger.SetEnabled();
          }
        }
        LogThis(logPrefix + "TryToEnableTriggersOn: LEAVE");
      }
      break;
    }
  }

  /**
   * Пробуем завершить работу триггера при разных событиях
   */
  void TryToDisable(MPG_TriggerEventType eventType) {
    switch (eventType) {
    case MPG_TriggerEventType.WIN:
      if (triggerDisableOnWin) {
        SetDisabled();
      }

      if (isDisabled) {
        LogThis(logPrefix + "FinishWorkingOn: WIN");
      }
      break;

    case MPG_TriggerEventType.LEAVE:
      if (!GetInsiders().Count()) {
        if (triggerDisableOnLeave) {
          SetDisabled();
        }

        if (isDisabled) {
          LogThis(logPrefix + "FinishWorkingOn: LEAVE");
        }
      }
      break;
    }
  }

  void TryToProcessMappingDataObjects(MPG_TriggerEventType eventType) {
    LogThis(logPrefix + "TryToProcessMappingDataObjects: " + mappingData.Count() + "; eventType: " + eventType);

    // Работаем только когда есть какие то объекты для спавна
    if (mappingData.Count()) {
      float maxDelay, currentMaxDelay;

      switch (eventType) {
      case MPG_TriggerEventType.STARTUP:
        LogThis(logPrefix + "SpawnMappingObjects: STARTUP;");
        foreach (MPG_Spawner_mappingData startupObject : mappingData) {
          // Если есть параметр addOnStartup, спавним
          if (startupObject.addOnStartup) {
            currentMaxDelay = ProcessMappingDataObjects(startupObject);

            if (maxDelay < currentMaxDelay) {
              maxDelay = currentMaxDelay;
            }
          }
        }

        // TODO Возможно стоит выполнять эту функцию сразу после спавна объектов, а не с максимальной задержкой
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateObjectsPathGraphLater, maxDelay, false);
        break;

      case MPG_TriggerEventType.ENTER:
        // Работаем, если ничего не размещалось и триггер не выключен
        if (!isSpawnedOnEnter && !isDisabled) {
          LogThis(logPrefix + "SpawnMappingObjects: ENTER;");
          isSpawnedOnEnter = true;
          foreach (MPG_Spawner_mappingData enterObject : mappingData) {
            // Если есть параметр addOnEnter, спавним
            if (enterObject.addOnEnter) {
              currentMaxDelay = ProcessMappingDataObjects(enterObject);

              if (maxDelay < currentMaxDelay) {
                maxDelay = currentMaxDelay;
              }
            }
          }

          // TODO Возможно стоит выполнять эту функцию сразу после спавна объектов, а не с максимальной задержкой
          GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateObjectsPathGraphLater, maxDelay, false);
        } else {
          if (isSpawnedOnEnter) {
            LogThis(logPrefix + "SpawnMappingObjects: ENTER Should not be spawn");
          }
        }

        // Чистим то, что должно чиститься при входе в триггер, если он не выключен
        if (objectsToRemoveOnEnter.Count() && !isDisabled) {
          LogThis(logPrefix + "objectsToRemoveOnEnter: " + objectsToRemoveOnEnter.Count());
          foreach (int index, Object delOnEnter : objectsToRemoveOnEnter) {
            if (delOnEnter) {
              LogThis(logPrefix + "MarkToDelete: " + delOnEnter + "; class: " + delOnEnter.GetType() + "; delay: " + objectsToRemoveOnEnterDelay[index] / 1000);
              GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, objectsToRemoveOnEnterDelay[index], false, delOnEnter);
            } else {
              Logger.Log(logPrefix + "ERROR: Cannot delete object from objectsToRemoveOnEnter");
            }
          }
          // После удаления чистим массивы
          objectsToRemoveOnEnter.Clear();
          objectsToRemoveOnEnterDelay.Clear();
        }

        if (isDisabled) {
          LogThis(logPrefix + "SpawnMappingObjects: ENTER Trigger is Disabled");
        }
        break;

      case MPG_TriggerEventType.FIRST_SPAWN:
        LogThis(logPrefix + "SpawnMappingObjects: FIRST_SPAWN;");
        // Работаем, если ничего не размещалось и триггер не выключен
        if (!isSpawnedOnFirstSpawn && !isDisabled) {
          isSpawnedOnFirstSpawn = true;
          foreach (MPG_Spawner_mappingData firstSpawnObject : mappingData) {
            // Если есть параметр addOnFirstSpawn, спавним
            if (firstSpawnObject.addOnFirstSpawn) {
              currentMaxDelay = ProcessMappingDataObjects(firstSpawnObject);

              if (maxDelay < currentMaxDelay) {
                maxDelay = currentMaxDelay;
              }
            }
          }

          // TODO Возможно стоит выполнять эту функцию сразу после спавна объектов, а не с максимальной задержкой
          GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateObjectsPathGraphLater, maxDelay, false);
        } else {
          if (isSpawnedOnFirstSpawn) {
            LogThis(logPrefix + "SpawnMappingObjects: FIRST_SPAWN Should not be spawn");
          }
        }

        // Чистим то, что должно чиститься при первом спавне
        if (objectsToRemoveOnFirstSpawn.Count() && !isDisabled) {
          LogThis(logPrefix + "objectsToRemoveOnFirstSpawn: " + objectsToRemoveOnFirstSpawn.Count());
          foreach (int index1, Object delOnFirstSpawn : objectsToRemoveOnFirstSpawn) {
            if (delOnFirstSpawn) {
              LogThis(logPrefix + "MarkToDelete: " + delOnFirstSpawn + "; class: " + delOnFirstSpawn.GetType() + "; delay: " + objectsToRemoveOnFirstSpawnDelay[index1] / 1000);
              GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, objectsToRemoveOnFirstSpawnDelay[index1], false, delOnFirstSpawn);
            } else {
              Logger.Log(logPrefix + "ERROR: Cannot delete object from objectsToRemoveOnFirstSpawn");
            }
          }
          // После удаления чистим массивы
          objectsToRemoveOnFirstSpawn.Clear();
          objectsToRemoveOnFirstSpawnDelay.Clear();
        }

        if (isDisabled) {
          LogThis(logPrefix + "SpawnMappingObjects: FIRST_SPAWN Trigger is Disabled");
        }
        break;

      case MPG_TriggerEventType.WIN:
        LogThis(logPrefix + "SpawnMappingObjects: WIN;");
        // Работаем, если ничего не размещалось и триггер не выключен
        if (!isSpawnedOnWin && !isDisabled) {
          isSpawnedOnWin = true;
          foreach (MPG_Spawner_mappingData winObject : mappingData) {
            // Если есть параметр addOnFirstSpawn, спавним
            if (winObject.addOnWin) {
              currentMaxDelay = ProcessMappingDataObjects(winObject);

              if (maxDelay < currentMaxDelay) {
                maxDelay = currentMaxDelay;
              }
            }
          }

          // TODO Возможно стоит выполнять эту функцию сразу после спавна объектов, а не с максимальной задержкой
          GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateObjectsPathGraphLater, maxDelay, false);
        } else {
          if (isSpawnedOnWin) {
            LogThis(logPrefix + "SpawnMappingObjects: WIN Should not be spawn");
          }
        }

        // Чистим то, что должно чиститься при убийстве всей живности
        if (objectsToRemoveOnWin.Count() && !isDisabled) {
          LogThis(logPrefix + "objectsToRemoveOnWin: " + objectsToRemoveOnWin.Count());
          foreach (int index2, Object delOnWin : objectsToRemoveOnWin) {
            if (delOnWin) {
              LogThis(logPrefix + "MarkToDelete: " + delOnWin + "; class: " + delOnWin.GetType() + "; delay: " + objectsToRemoveOnWinDelay[index2] / 1000);
              GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, objectsToRemoveOnWinDelay[index2], false, delOnWin);
            } else {
              Logger.Log(logPrefix + "ERROR: Cannot delete object from objectsToRemoveOnWin");
            }
          }
          // После удаления чистим массивы
          objectsToRemoveOnWin.Clear();
          objectsToRemoveOnWinDelay.Clear();
        }
        if (isDisabled) {
          LogThis(logPrefix + "SpawnMappingObjects: WIN Trigger is Disabled");
        }
        break;
      }
    }
  }

  void UpdateObjectsPathGraphLater() {
    GetGame().GetWorld().ProcessMarkedObjectsForPathgraphUpdate();
  }

  /**
   * Запускаем процесс спавна объектов с задержкой.
   * Возвращаем максимальную задержку в миллесекундах для того, что бы в конце цикла можно было запустить
   * функцию `GetGame().GetWorld().ProcessMarkedObjectsForPathgraphUpdate();` с нужной задержкой
   */
  float ProcessMappingDataObjects(MPG_Spawner_mappingData mappingDataObject) {
    float maxDelay = 0;

    if (maxDelay < mappingDataObject.addDelay) {
      maxDelay = mappingDataObject.addDelay;
    }

    if (mappingDataObject.mappingObjects && mappingDataObject.mappingObjects.Count()) {
      LogThis(logPrefix + "mappingObjects: " + mappingDataObject.mappingObjects.Count() + "; addDelay: " + mappingDataObject.addDelay + "; removeDelay: " + mappingDataObject.removeDelay);

      foreach (ITEM_SpawnerObject mappingObject : mappingDataObject.mappingObjects) {
        int addDelay = mappingDataObject.addDelay * 1000;
        int removeDelay = mappingDataObject.removeDelay * 1000;
        // TODO Попробовать переделать на спавн с задержкой всех объектов сразу, а не по одному,
        //  есть подозрение, что спавнить по одному с задержкой дороже, чем спавнить все с задержкой.
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.SpawnMappingDataObject, addDelay, false, mappingObject, mappingDataObject.removeOnEnter, mappingDataObject.removeOnFirstSpawn, mappingDataObject.removeOnWin, removeDelay);
      }
    }

    return maxDelay;
  }
  /**
   * Добавляем объект на карту с задержкой
   */
  void SpawnMappingDataObject(ITEM_SpawnerObject object, bool removeOnEnter, bool removeOnFirstSpawn, bool removeOnWin, int removeDelay) {
    InsertToRemoveList(SpawnMappingObject(object), removeOnEnter, removeOnFirstSpawn, removeOnWin, removeDelay);
  }

  /**
   * Функция спавна объекта на карту, основа - дефолтный ObjectSpawner.
   * Сделал чтобы можно было использовать конфиг от ObjectSpawner без дополнительных преобразований.
   */
  Object SpawnMappingObject(ITEM_SpawnerObject item) {
    Object object;

    float scale = item.scale;
    if (scale == 0) {
      scale = 1;
    }

    int flags = ECE_SETUP | ECE_UPDATEPATHGRAPH | ECE_CREATEPHYSICS | ECE_NOLIFETIME | ECE_DYNAMIC_PERSISTENCY;

    if (item.enableCEPersistency) {
      flags &= ~ECE_DYNAMIC_PERSISTENCY;
      flags &= ~ECE_NOLIFETIME;
    }

    object = GetGame().CreateObjectEx(item.name, vector.ArrayToVec(item.pos), flags, RF_IGNORE);
    if (object) {
      object.SetOrientation(vector.ArrayToVec(item.ypr));
      if (item.scale != 1) {
        object.SetScale(scale);
      }
      LogThis(logPrefix + "Spawned: " + item.name + "; pos: " + vector.ArrayToVec(item.pos));

    } else {
      Logger.Log(logPrefix + "ERROR: " + item.name + " NOT Created");
    }

    return object;
  }

  /**
   * Добавляем объекты в массив, что бы потом можно было легче удалить.
   * Добавляем в тот массив, из которого потом будем удалять в зависимости от параметра `removeOn...`.
   * Так же во второй одноимённый массив добавляем задержку по времени для удаления.
   */
  void InsertToRemoveList(Object object, bool removeOnEnter, bool removeOnFirstSpawn, bool removeOnWin, int removeDelay) {
    if (object) {
      string objType = object.GetType();

      LogThis(logPrefix + "InsertToRemoveList: " + object + "; removeOnEnter: " + removeOnEnter + "; removeOnFirstSpawn: " + removeOnFirstSpawn + "; removeOnWin: " + removeOnWin + "; removeDelay: " + removeDelay / 1000 + "; type: " + object.GetType());

      if (removeOnEnter) {
        objectsToRemoveOnEnter.Insert(object);
        objectsToRemoveOnEnterDelay.Insert(removeDelay);
        LogThis(logPrefix + "insertTo: removeOnEnter; object: " + objType);
      }
      if (removeOnFirstSpawn) {
        objectsToRemoveOnFirstSpawn.Insert(object);
        objectsToRemoveOnFirstSpawnDelay.Insert(removeDelay);
        LogThis(logPrefix + "insertTo: removeOnFirstSpawn; object: " + objType);
      }
      if (removeOnWin) {
        objectsToRemoveOnWin.Insert(object);
        objectsToRemoveOnWinDelay.Insert(removeDelay);
        LogThis(logPrefix + "insertTo: removeOnWin; object: " + objType);
      }
    }
  }

  // clang-format off
  private int GetRandInt(string ristr) {
    // clang-format on
    int retI;
    if (ristr.Contains("-")) {
      TStringArray rInt = new TStringArray;
      ristr.Split("-", rInt);
      retI = Math.RandomIntInclusive(rInt[0].ToInt(), rInt[1].ToInt());
    } else {
      retI = ristr.ToInt();
    }

    return retI;
  }
  // clang-format off
  private float GetRandFloat(string rfstr) {
    // clang-format on
    float retF;
    if (rfstr.Contains("-")) {
      TStringArray rFlo = new TStringArray;
      rfstr.Split("-", rFlo);
      retF = Math.RandomFloatInclusive(rFlo[0].ToFloat(), rFlo[1].ToFloat());
    } else {
      retF = rfstr.ToFloat();
    }
    return retF;
  }

  // clang-format off
  private void LogThis(string message) {
    // clang-format on
    // Пишем в лог только тогда, когда включен дебаг точки
    if (isDebugEnabled) {
      Logger.Log(message);
    }
  }

  /**
   * Функция для склонения русских слов в зависимости от числа
   * Принимает число и варианты склонений для единицы, двойки и множества.
   * Возвращает слово с правильным окончанием
   *
   * Примеры использования:
   *
   *
   * Declension(1,"бухан|ка|ки|ок"); // буханка
   * Declension(-101,"бухан|ка|ки|ок"); // буханка
   * Declension(2,"бухан|ка|ки|ок"); // буханки
   * Declension(-332,"бухан|ка|ки|ок"); // буханки
   * Declension(5,"бухан|ка|ки|ок"); // буханок
   * Declension(-555,"бухан|ка|ки|ок"); // буханок
   */
  // clang-format off
  private string Declension(int n, string words) {
    // clang-format on
    ref TStringArray wordList = new TStringArray;
    words.Split("|", wordList);

    n = Math.AbsInt(n);
    string result;
    int n10 = n % 10;
    int n100 = n % 100;

    if (n10 == 1 && n100 != 11) {
      // буханка
      result = wordList[0] + wordList[1];
    } else if (n10 >= 2 && n10 <= 4 && (n100 < 10 || n100 >= 20)) {
      // буханки
      result = wordList[0] + wordList[2];
    } else {
      // буханок
      result = wordList[0] + wordList[3];
    }

    return result;
  }
};
