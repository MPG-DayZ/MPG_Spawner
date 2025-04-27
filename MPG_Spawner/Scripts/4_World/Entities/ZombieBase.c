modded class ZombieBase extends DayZInfected {
  // clang-format off
  private ref MPG_SpawnerEntity m_SpawnerEntity;
  // clang-format on

  void ZombieBase() {
    m_SpawnerEntity = new MPG_SpawnerEntity(this);
  }

  void SetMPG_Spawner_Flag() {
    m_SpawnerEntity.SetFlag();
  }

  override bool ResistContaminatedEffect() {
    if (m_SpawnerEntity && m_SpawnerEntity.GetFlag()) {
      return true;
    }

    return super.ResistContaminatedEffect();
  }

  override void EEHitBy(TotalDamageResult damageResult,
                        int damageType,
                        EntityAI source,
                        int component,
                        string dmgZone,
                        string ammo,
                        vector modelPos,
                        float speedCoef) {
    m_SpawnerEntity.HandleEEHitBy();

    if (!IsAlive() && m_SpawnerEntity) {
      m_SpawnerEntity.HandleDeath(source);
    }

    super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
  }

  void SetMPG_SPWNR_PointId(int pointId) {
    m_SpawnerEntity.SetPointId(pointId);
  }

  void SetMPG_SPWNR_Timer(int seconds) {
    m_SpawnerEntity.SetClearTimer(seconds);
  }
}