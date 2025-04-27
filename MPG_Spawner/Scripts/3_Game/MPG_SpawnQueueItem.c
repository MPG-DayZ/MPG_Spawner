// Класс для хранения элементов очереди спавна
class MPG_SpawnQueueItem {
  string m_Position;
  string m_Orientation;
  ref TStringArray m_SpawnItemArr;
  vector m_SpawnPos;
  bool m_ShouldRotate;

  void MPG_SpawnQueueItem(string position, string orientation, TStringArray spawnItemArr, vector spawnPos, bool shouldRotate) {
    m_Position = position;
    m_Orientation = orientation;
    m_SpawnItemArr = spawnItemArr;
    m_SpawnPos = spawnPos;
    m_ShouldRotate = shouldRotate;
  }
}