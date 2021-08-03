using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class MapManager : MonoBehaviour
{
    public int Width;
    public int Height;
    public int GoalX;
    public int GoalY;
    public int[,] Map;
    public Text ClearText;
    public GameObject Minimap;

    // Start is called before the first frame update
    private void Awake()
    {
        Map = new int[Width, Height];

        for(int i = 0; i < Width; i++)
        {
            for (int j = 0; j < Height; j++)
            {
                Map[i, j] = 0;
            }
        }
    }

    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        if(Map[GoalX,GoalY] == 2)
        {
            SceneManager.LoadScene("Clear");
        }
    }

    public void PrintMap()
    {
        string str = " ";

        for (int i = 0; i < Width; i++)
        {
            str = " ";
            for (int j = 0; j < Height; j++)
            {
               str += "  [" + i.ToString() + "," + j.ToString() + "] =" + Map[i, j].ToString();
            }
            Debug.Log(str);
        }
    }

    public void SetVisibleMinimap(bool _Input)
    {
        Minimap.active = _Input;
    }

}
