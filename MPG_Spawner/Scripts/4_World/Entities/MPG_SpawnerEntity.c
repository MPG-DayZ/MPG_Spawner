class MPG_SpawnerEntity {
  // clang-format off
  private int m_PointId;
  private int m_ClearTimer;
  private bool m_Flag;
  private EntityAI m_Owner;
  private bool m_IsHitted;
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
        g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(g_Game.ObjectDelete, m_ClearTimer * 1000, false, m_Owner);
      }

      MPG_Spawner.GetInstance().RemoveSpawnedCreature(m_PointId, m_Owner.GetID(), killer);
      m_PointId = 0;
    }
  }

  void HandleEEHitBy() {
    if (!m_IsHitted) {
      MPG_Spawner.GetInstance().SetTriggerDisableReset(m_PointId);
    }

    m_IsHitted = true;
  }
}