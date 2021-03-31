using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Room_UIController : MonoBehaviour
{
    public GameObject[] stageDoor = new GameObject[3];
    public Text[,] record = new Text[3, 2];
    bool[] stageOpen = new bool[3];

    static int whatStage = 1;

    public GameObject[] NPC = new GameObject[2];

    Animator doorAnimator;

    public bool meetPartner1;
    public bool meetPartner2;

    public GameObject[] explainPartner = new GameObject[2];

    public GameObject[] button = new GameObject[2];
    public GameObject costume;
    public GameObject costume_select;
    public GameObject all_model;
    public GameObject[] model = new GameObject[3];
    int model_num;

    void Start()
    {
        meetPartner1 = false;
        meetPartner2 = false;

        stageOpen[0] = GameObject.Find("DataController").GetComponent<DataController>().GetStage1Open();
        stageOpen[1] = GameObject.Find("DataController").GetComponent<DataController>().GetStage2Open();
        stageOpen[2] = GameObject.Find("DataController").GetComponent<DataController>().GetStage3Open();

        if (stageOpen[0])
        {
            doorAnimator = stageDoor[0].GetComponent<Animator>();
            doorAnimator.SetBool("open", true);
        }
        if (stageOpen[1])
        {
            doorAnimator = stageDoor[1].GetComponent<Animator>();
            doorAnimator.SetBool("open", true);
        }
        if (stageOpen[2])
        {
            doorAnimator = stageDoor[2].GetComponent<Animator>();
            doorAnimator.SetBool("open", true);
        }

        record[0, 0] = GameObject.Find("Stage1").transform.Find("record").GetComponent<Text>();
        record[0, 1] = GameObject.Find("Stage1").transform.Find("star").GetComponent<Text>();
        record[1, 0] = GameObject.Find("Stage2").transform.Find("record").GetComponent<Text>();
        record[1, 1] = GameObject.Find("Stage2").transform.Find("star").GetComponent<Text>();
        record[2, 0] = GameObject.Find("Stage3").transform.Find("record").GetComponent<Text>();
        record[2, 1] = GameObject.Find("Stage3").transform.Find("star").GetComponent<Text>();

        float time = GameObject.Find("DataController").GetComponent<DataController>().Get_StageTime(1);
        if (time == 0) return;
        record[0, 0].text = "Best : " + (int)time / 60 + ":" + (int)time % 60;
        if (time <= 90f)
            record[0, 1].text = "★ ★ ★";
        else if (time > 90f && time <= 120f)
            record[0, 1].text = "★ ★ ☆";
        else if (time > 120f && time <= 180f)
            record[0, 1].text = "★ ☆ ☆";
        else
            record[0, 1].text = "☆ ☆ ☆";

        time = GameObject.Find("DataController").GetComponent<DataController>().Get_StageTime(2);
        if (time == 0) return;
        record[1, 0].text = "Best : " + (int)time / 60 + ":" + (int)time % 60;
        if (time <= 90f)
            record[1, 1].text = "★ ★ ★";
        else if (time > 90f && time <= 120f)
            record[1, 1].text = "★ ★ ☆";
        else if (time > 120f && time <= 180f)
            record[1, 1].text = "★ ☆ ☆";
        else
            record[1, 1].text = "☆ ☆ ☆";

        time = GameObject.Find("DataController").GetComponent<DataController>().Get_StageTime(3);
        if (time == 0) return;
        record[2, 0].text = "Best : " + (int)time / 60 + ":" + (int)time % 60;
        if (time <= 90f)
            record[2, 1].text = "★ ★ ★";
        else if (time > 90f && time <= 120f)
            record[2, 1].text = "★ ★ ☆";
        else if (time > 120f && time <= 180f)
            record[2, 1].text = "★ ☆ ☆";
        else
            record[2, 1].text = "☆ ☆ ☆";
    }

    void Update()
    {
        if (meetPartner1)
        {
            explainPartner[0].SetActive(true);
            NPC[0].GetComponent<Animator>().SetBool("speak", true);
        }
        else
        {
            explainPartner[0].SetActive(false);
            NPC[0].GetComponent<Animator>().SetBool("speak", false);
        }

        if (meetPartner2)
        {
            explainPartner[1].SetActive(true);
            NPC[1].GetComponent<Animator>().SetBool("speak", true);
        }
        else
        {
            explainPartner[1].SetActive(false);
            NPC[1].GetComponent<Animator>().SetBool("speak", false);
        }
    }

    public void Exit()
    {
        Application.Quit();
    }

    public void ChangeCostume()
    {
        button[0].SetActive(false);
        button[1].SetActive(false);
        GameObject.Find("Player").GetComponent<Room_Move>().do_costume = true;
        costume.SetActive(true);
    }

    public void BackChangeCostume()
    {
        button[0].SetActive(true);
        button[1].SetActive(true);
        GameObject.Find("Player").GetComponent<Room_Move>().do_costume = false;
        costume.SetActive(false);
    }

    public void SelectModel(int num)
    {        
        costume_select.SetActive(false);
        all_model.SetActive(true);
        model[num].SetActive(true);
        model_num = num;
    }

    public void BackSelectModel()
    {
        costume_select.SetActive(true);
        model[model_num].SetActive(false);
        all_model.SetActive(false);
    }

    public void SelectCostume(int num)
    {
        GameObject.Find("DataController").GetComponent<DataController>().Set_costume(model_num, num);
    }
}
