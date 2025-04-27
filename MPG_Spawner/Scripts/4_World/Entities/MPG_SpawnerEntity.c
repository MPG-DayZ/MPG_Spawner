class MPG_SpawnerEntity {
  // clang-format off
  private int m_PointId;
  private int m_ClearTimer;
  private bool m_Flag;
  private EntityAI m_Owner;
  // clang-format on

  void MPG_SpawnerEntity(EntityAI owner) {
    m_Owner = owner;
    m_PointId = 0;
    m_ClearTimer = 0;
    m_Flag = false;
  }

  void SetFlag() {
    m_Flag = true;
  }

  bool GetFlag() {
    return m_Flag;
  }

  void SetPointId(int pointId) {
    m_PointId = pointId;
  }

  void SetClearTimer(int seconds) {
    m_ClearTimer = seconds;
  }

  void HandleDeath(Object killer) {
    if (m_PointId) {
      if (m_Owner && m_ClearTimer) {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, m_ClearTimer * 1000, false, m_Owner);
      }

      MPG_Spawner.GetInstance().RemoveSpawnedCreature(m_PointId, m_Owner.GetID(), killer);
      m_PointId = 0;
    }
  }
}