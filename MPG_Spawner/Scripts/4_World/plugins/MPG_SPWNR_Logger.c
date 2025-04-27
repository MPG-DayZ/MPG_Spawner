class MPG_SPWNR_Logger extends PluginBase {
  FileHandle m_LogFile;

  void MPG_SPWNR_Logger() {
    if (isHost()) {
      Print(MPG_SPWNR + " Logger Init");

      if (!FileExist(MPG_SPWNR_ROOT_DIR)) {
        Print(MPG_SPWNR + "'" + MPG_SPWNR_ROOT_DIR + "' does not exist, creating...");
        MakeDirectory(MPG_SPWNR_ROOT_DIR);
      }

      if (!FileExist(MPG_SPWNR_LOGS_DIR)) {
        Print(MPG_SPWNR + "'" + MPG_SPWNR_LOGS_DIR + "' does not exist, creating...");
        MakeDirectory(MPG_SPWNR_LOGS_DIR);
      }

      if (!FileExist(MPG_SPWNR_LOGS_ARCHIVES_DIR)) {
        Print(MPG_SPWNR + "'" + MPG_SPWNR_LOGS_ARCHIVES_DIR + "' does not exist, creating...");
        MakeDirectory(MPG_SPWNR_LOGS_ARCHIVES_DIR);
      }

      if (FileExist(MPG_SPWNR_LOGS_FILENAME)) {
        string currentTime = GetDate() + "_" + GetTime("-");
        string newFileName = MPG_SPWNR_LOGS_ARCHIVES_DIR + currentTime + ".log";

        CopyFile(MPG_SPWNR_LOGS_FILENAME, newFileName);
        DeleteFile(MPG_SPWNR_LOGS_FILENAME);
      }

      CreateNewLogFile();
    }
  };

  void ~MPG_SPWNR_Logger() {
    if (isHost()) {
      Print(MPG_SPWNR + " Logger Closed");
      CloseFile(m_LogFile);
    }
  };

  bool isHost() {
    if (!g_Game) {
      return false;
    }

    //    return g_Game.IsServer() && g_Game.IsMultiplayer();
    return g_Game.IsMultiplayer();
  }

  void CreateNewLogFile() {
    Print(MPG_SPWNR + " Logger Create Log File");

    if (isHost()) {
      m_LogFile = OpenFile(MPG_SPWNR_LOGS_FILENAME, FileMode.WRITE);

      if (m_LogFile != 0) {
        string currentTime = GetDate() + "_" + GetTime();

        FPrintln(m_LogFile, "Log Created: " + currentTime);
      } else {
        Print(MPG_SPWNR + "ERROR:  Unable to create " + MPG_SPWNR_LOGS_FILENAME);
      }
    }
  };

  void Log(string text) {
    if (isHost()) {
      string currentTime = GetTime() + " | ";
      FPrintln(m_LogFile, currentTime + text);
    }
  };

  static string GetDate(string sep = "-") {
    int year, month, day;
    GetYearMonthDay(year, month, day);

    string y = year.ToString();
    string m = month.ToString();
    string d = day.ToString();

    if (m.Length() == 1) {
      m = "0" + m;
    }

    if (d.Length() == 1) {
      d = "0" + d;
    }

    return y + sep + m + sep + d;
  }

  static string GetTime(string sep = ":") {
    int hour, minute, second;
    GetHourMinuteSecond(hour, minute, second);

    string h = hour.ToString();
    if (h.Length() == 1) {
      h = "0" + h;
    }

    string m = minute.ToString();
    if (m.Length() == 1) {
      m = "0" + m;
    }

    string s = second.ToString();
    if (s.Length() == 1) {
      s = "0" + s;
    }

    return h + sep + m + sep + s;
  }

  static string GetParedPosition(vector position) {
    if (position) {
      return position[0].ToString() + "," + position[2].ToString();
    }

    return "0,0";
  }

  static string GetPlayerInfo(PlayerBase player) {
    if (player) {
      string pPosition = GetParedPosition(player.GetPosition());
      string pSteamId = player.GetIdentity().GetPlainId();
      string pName = player.GetIdentity().GetName();
      string playerInfo = "steamId: " + pSteamId + "; name: " + pName + "; playerPos: " + pPosition + "; ";

      return playerInfo;
    }
    return "steamId: none; name: none; playerPos: 0,0; ";
  }
};