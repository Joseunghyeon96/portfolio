using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Title_UIController : MonoBehaviour
{
    public GameObject all_button;
    public GameObject explain;

    void Start()
    {
        explain.SetActive(false);
    }

    public void Back()
    {
        explain.SetActive(false);
        all_button.SetActive(true);
    }

    public void Explain()
    {
        explain.SetActive(true);
        all_button.SetActive(false);
    }

    public void GameStart()
    {
        SceneManager.LoadScene("Room");
    }

    public void Exit()
    {
        Application.Quit();
    }
}
