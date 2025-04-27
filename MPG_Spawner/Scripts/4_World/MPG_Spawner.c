class MPG_Spawner {
  MPG_SPWNR_Logger Logger = MPG_SPWNR_Logger.Cast(GetPlugin(MPG_SPWNR_Logger));
  MPG_SPWNR_ModConfig MPG_SPWNR_Config = g_MPG_SPWNR_ModConfig;

  // clang-format off
  protected static ref MPG_Spawner Instance;
  protected ref map<int, ref TIntArray> spawnedCreatures;
  protected ref map<int, ref TIntArray> spawnedLoot;
  protected ref array<MPG_Trigger> m_Triggers;
  private ref map<int, ref MPG_Spawner_PointConfig> PointsConfigsData = new map<int, ref MPG_Spawner_PointConfig>();
  // clang-format on

  static MPG_Spawner GetInstance() {
    if (!Instance) {
      Instance = new MPG_Spawner();
    }
    return Instance;
  }

  static void ClearInstance() { Instance = null; }

  void ResetTriggers() {
    if (Instance) {
      LogThis("ClearInstance: START");

      foreach (MPG_Trigger triggerItem : m_Triggers) {
        triggerItem.DeleteTrigger();
        GetGame().ObjectDelete(triggerItem);
      }
      m_Triggers.Clear();
      LogThis("ClearInstance: END");
    }

    // Instance = null;
    ClearInstance();
  }

  array<MPG_Trigger> GetTriggers() { return m_Triggers; }

  void AddPointToPool(MPG_Trigger trigger) {
    m_Triggers.Insert(trigger);
    LogThis("Points: AddPoint; TotalCount: " + m_Triggers.Count());
  }

  void MPG_Spawner() {

    if (MPG_SPWNR_Config.isModDisabled) {
      Logger.Log("MPG_Spawner: DISABLED;");
    } else {

      Logger.Log("MPG_Spawner: STARTED;");
      LoadPointsConfigsData();

      if (MPG_SPWNR_Config.isDebugEnabled) {
        Logger.Log("MPG_Spawner: DEBUG ENABLED;");
#ifndef MPG_SPAWN_ZONE
        Logger.Log("MPG_Spawner: WARNING: Trigger visualization is not possible because the MPG_spawn_zone mod is not loaded;");
#endif
      }

      m_Triggers = new array<MPG_Trigger>;
      spawnedCreatures = new map<int, ref TIntArray>;
      spawnedLoot = new map<int, ref TIntArray>;

      MPG_Trigger trigger;

      Logger.Log("Points To Load: " + PointsConfigsData.Count());

      // clang-format off
      foreach (MPG_Spawner_PointConfig pointConfig : PointsConfigsData) {
        // clang-format on

        if (!pointConfig) {
          continue;
        }

        string posrot = pointConfig.triggerPosition;

        // Заменим запятые на пробелы и двойные пробелы на одинарные,
        // что бы избегать ошибок при спавне и неправильном написании координат
        // TODO Реализовать конвертацию в нужный формат при загрузке конфигов с последующим сохранением.
        posrot.Replace(",", " ");
        posrot.Replace("  ", " ");

        TStringArray loc = new TStringArray;
        posrot.Split("|", loc);
        string posStr = loc.Get(0);
        string rot = loc.Get(1);

        if (!rot) {
          rot = "0 0 0";
        }

        vector pos = posStr.ToVector();

        if (pos[1] == 0) {
          pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        }

        trigger = MPG_Trigger.Cast(GetGame().CreateObject("MPG_Trigger", pos));

        trigger.CreateMPGTrigger(pointConfig, pos, rot.ToVector());

        AddPointToPool(trigger);
      }
    }
  }

  void AddSpawnedInstance(int pointId, int objectId) {
    TIntArray inTriggerCreatures = spawnedCreatures.Get(pointId);
    if (!inTriggerCreatures) {
      inTriggerCreatures = new TIntArray;
    }
    inTriggerCreatures.Insert(objectId);
    spawnedCreatures.Set(pointId, inTriggerCreatures);

    LogThis("PointId: " + pointId + "; AddCreatureId: " + objectId);
  }

  void RemoveSpawnedCreature(int pointId, int objectId, Object killer, bool canWin = true) {
    if (spawnedCreatures.Count() && killer) {

      TIntArray pointItem = spawnedCreatures.Get(pointId);

      if (pointItem) {
        pointItem.RemoveItem(objectId);

        LogThis("PointId: " + pointId + "; RemoveObjectId: " + objectId);

        if (pointItem.Count() < 1 && canWin) {
          EntityAI parentEntity = EntityAI.Cast(killer);

          if (parentEntity) {
            Man player = parentEntity.GetHierarchyRootPlayer();

            if (player) {
              for (int i = 0; i < m_Triggers.Count(); i++) {
                if (m_Triggers.Get(i).GetPointId() == pointId) {
                  MPG_Trigger curPoint = m_Triggers.Get(i);

                  int notificationTime = curPoint.GetNotificationTime();
                  string notificationTitle = curPoint.GetNotificationTitle();
                  string notificationTextWin = curPoint.GetNotificationTextWin();
                  string notificationIcon = curPoint.GetNotificationIcon();

                  if (notificationTextWin != "" && !curPoint.isTriggerDisabled()) {
                    NotificationSystem.SendNotificationToPlayerExtended(player, notificationTime, notificationTitle, notificationTextWin, notificationIcon);
                    Logger.Log("PointId: " + pointId + "; Winner: " + Logger.GetPlayerInfo(PlayerBase.Cast(player)));
                  }

                  curPoint.TryToProcessMappingDataObjects(MPG_TriggerEventType.WIN);
                  curPoint.TryToDisable(MPG_TriggerEventType.WIN);
                  curPoint.TryToEnableTriggers(MPG_TriggerEventType.WIN);

                  break;
                }
              }
            }
          }
        }
      }
    }
  }

  void AddSpawnedLoot(int pointId, int lootId) {
    TIntArray inTriggerLoot = spawnedLoot.Get(pointId);
    if (!inTriggerLoot) {
      inTriggerLoot = new TIntArray;
    }
    inTriggerLoot.Insert(lootId);
    spawnedLoot.Set(pointId, inTriggerLoot);

    LogThis("PointId: " + pointId + "; AddLootId: " + lootId);
  }

  void RemoveSpawnedLoot(int pointId, int lootId) {
    //// пока не используется
  }

  TIntArray GetSpawnedCreatures(int pointId) {
    if (spawnedCreatures) {
      return spawnedCreatures.Get(pointId);
    }
    return NULL;
  }

  TIntArray GetSpawnedLoot(int pointId) {
    if (spawnedLoot) {
      return spawnedLoot.Get(pointId);
    }
    return NULL;
  }

  void LoadPointsConfigsData() {
    TStringArray fileNames = MPG_SPWNR_Config.pointsConfigs;

    ref array<MPG_Spawner_PointConfig> tmpArr = {};

    // clang-format off
      foreach (string fileName : fileNames) {
      // clang-format on
      array<MPG_Spawner_PointConfig> tempData = {};
      JsonFileLoader<array<MPG_Spawner_PointConfig>>.JsonLoadFile(MPG_SPWNR_POINTS_DIR + fileName + ".json", tempData);

      tmpArr.InsertAll(tempData);
    }

    for (int i = 0; i < tmpArr.Count(); i++) {
      bool isCreated;
      int pointId;
      MPG_Spawner_PointConfig pointConf = tmpArr[i];
      isCreated = GetGame().GameScript.CallFunction(pointConf, "GetId", pointId, 0);

      if (isCreated) {
        PointsConfigsData.Insert(pointId, pointConf);
      } else {
        Logger.Log(string.Format("ERROR: Config NOT Loaded; pointId: %1;", pointId));
      }
    }
  }

  // clang-format off
    private void LogThis(string message) {
    // clang-format on
    if (MPG_SPWNR_Config.isDebugEnabled) {
      Logger.Log(message);
    }
  }
}
