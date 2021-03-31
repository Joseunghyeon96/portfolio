using UnityEngine;
using UnityEngine.UI;

public class Counter : MonoBehaviour
{
    #region Sigleton
    private static Counter instance;
    public static Counter Instance
    {
        get
        {
            if (instance == null)
                instance = FindObjectOfType<Counter>();
            return instance;
        }
    }
    #endregion

    private int max;
    public int count;
    public int killCount
    {
        get { return max - count; }
    }

    public GameObject countText;
    public GameObject destroyCountText;

    private void OnEnable()
    {
        max = transform.childCount;
        count = max;
        SetCount(countText, count);
    }

    private void Update()
    {
        if (max != count) UpdateCount();
        else if(count <= 0) SetGameState("GameClear");
    }

    public void SetCount(GameObject go, int count)
    {
        go.transform.Find("count").GetComponent<Text>().text = count.ToString();
    }

    public void UpdateCount()
    {
        SetCount(countText, count);
        SetCount(destroyCountText, killCount);
    }

    public GameObject wGameState;
    public void SetGameState(string state)
    {
        wGameState.SetActive(true);
        wGameState.transform.Find("GameState").GetComponent<Text>().text = state;
        SetCount(wGameState.transform.Find("Kill").gameObject, killCount);
    }
}
