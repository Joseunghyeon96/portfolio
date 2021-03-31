using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameClear : MonoBehaviour
{
    public GameObject potal;
    int rotateVal = 0;
     void Update()
    {
        rotateVal += 5;
        potal.transform.rotation = Quaternion.Euler(0, 0, rotateVal);
    }

    public void GameOver()
    {
        Application.Quit();
    }

    public void GoTitle()
    {
        SceneManager.LoadScene("Title");
    }

    public void GoRoom()
    {
        SceneManager.LoadScene("Room");
    }
}
