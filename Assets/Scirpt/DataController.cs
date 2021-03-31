using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DataController : MonoBehaviour
{
    static float[] stageTime = new float[3] { 0, 0, 0 };

    static bool stage1Open = true;
    static bool stage2Open = false;
    static bool stage3Open = false;

    static int curStage = 1;

    static int[] costume = new int[3] { 0, 0, 0 };

    static int player_seq = 0;


    public float Get_StageTime(int num)
    {
        return stageTime[num - 1];
    }

    public void Set_StageTime(int num, float time)
    {
        if (stageTime[num - 1] != 0 && stageTime[num - 1] <= time)
            return;
        stageTime[num - 1] = time;
    }

    public bool GetStage1Open()
    {
        return stage1Open;
    }

    public bool GetStage2Open()
    {
        return stage2Open;
    }

    public bool GetStage3Open()
    {
        return stage3Open;
    }

    public void SetStageOpen(int num)
    {
        if (num == 1)
            stage1Open = true;
        if (num == 2)
            stage2Open = true;
        if (num == 3)
            stage3Open = true;
    }

    public int Get_curStage()
    {
        return curStage;
    }

    public void Set_curStage(int num)
    {
        curStage = num;
    }

    public int Get_costume(int model_num)
    {
        return costume[model_num];
    }

    public void Set_costume(int model_num, int costume_num)
    {
        costume[model_num] = costume_num;
    }

    public int Get_playerSeq()
    {
        return player_seq;
    }

    public void Plus_playerSeq()
    {
        if (curStage == 1)
        {
            if (player_seq < 1)
                player_seq = 1;
        }
        if (curStage == 2)
        {
            if (player_seq < 2)
                player_seq = 2;
        }
    }
}
