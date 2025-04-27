modded class MissionServer extends MissionBase {
  // Ждём исправления бага https://feedback.bistudio.com/T183081
  // void MissionServer() { Использовать нельзя
  override void OnInit() {
    super.OnInit();
    if (GetGame().IsServer() || !GetGame().IsMultiplayer()) {
      g_MPG_SPWNR_ModConfig = NULL;
      GetMPG_SPWNR_ModConfig();

      MPG_Spawner.ClearInstance();
      MPG_Spawner.GetInstance();
    }
  }
}
