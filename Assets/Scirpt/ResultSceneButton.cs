using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ResultSceneButton : MonoBehaviour
{
    string nextScene;

    public void ReStart()
    {
        nextScene = "Stage"+ GameObject.Find("DataController").GetComponent<DataController>().Get_curStage();
        SceneManager.LoadScene(nextScene);
    }

    public void BackRoom()
    {
        SceneManager.LoadScene("Room");
    }
}
