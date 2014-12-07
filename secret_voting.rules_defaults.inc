<?php
/**
 * @file
 * secret_voting.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function secret_voting_default_rules_configuration() {
  $items = array();
  $items['rules_invite_all_voters'] = entity_import('rules_config', '{ "rules_invite_all_voters" : {
      "LABEL" : "Invite all voters",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Voting" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "vote" : { "label" : "Vote", "type" : "node" } },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "NOT data_is" : { "data" : [ "vote:field-vote-state" ], "value" : "closed" } }
      ],
      "DO" : [
        { "component_rules_voting_invite_voters" : { "vote" : [ "vote" ] } },
        { "component_secret_voting_invite_voters_public" : { "vote" : [ "vote" ] } }
      ]
    }
  }');
  $items['rules_voting_change_vote_state_when_voting'] = entity_import('rules_config', '{ "rules_voting_change_vote_state_when_voting" : {
      "LABEL" : "Change Vote state when voting",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Secret Voting" ],
      "REQUIRES" : [ "rules", "eck" ],
      "ON" : { "vote_token_insert" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "vote-token" ], "field" : "field_token_vote" } },
        { "entity_is_of_bundle" : {
            "entity" : [ "vote-token:field-token-vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "data_is" : {
            "data" : [ "vote-token:field-token-vote:field-vote-state" ],
            "value" : "open"
          }
        }
      ],
      "DO" : [
        { "data_set" : {
            "data" : [ "vote-token:field-token-vote:field-vote-state" ],
            "value" : "ongoing"
          }
        },
        { "entity_save" : { "data" : [ "vote-token:field-token-vote" ] } }
      ]
    }
  }');
  $items['rules_voting_close_vote'] = entity_import('rules_config', '{ "rules_voting_close_vote" : {
      "LABEL" : "Close vote",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Voting" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "vote" : { "label" : "Vote", "type" : "node" } },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "NOT data_is" : { "data" : [ "vote:field-vote-state" ], "value" : "closed" } }
      ],
      "DO" : [
        { "data_set" : { "data" : [ "vote:field-vote-state" ], "value" : "closed" } },
        { "entity_save" : { "data" : [ "vote" ] } }
      ]
    }
  }');
  $items['rules_voting_create_all_tokens_when_closing_the_vote'] = entity_import('rules_config', '{ "rules_voting_create_all_tokens_when_closing_the_vote" : {
      "LABEL" : "Create all tokens when closing the vote",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Secret Voting" ],
      "REQUIRES" : [ "rules", "secret_voting" ],
      "ON" : { "node_update--vote" : { "bundle" : "vote" } },
      "IF" : [
        { "data_is" : { "data" : [ "node:field-vote-state" ], "value" : "closed" } },
        { "NOT data_is" : { "data" : [ "node-unchanged:field-vote-state" ], "value" : "closed" } },
        { "data_is" : { "data" : [ "node:field-vote-secret" ], "value" : 1 } }
      ],
      "DO" : [
        { "voting_generate_token" : { "PROVIDE" : { "secret_token" : { "secret_token" : "Secret token" } } } },
        { "component_rules_voting_get_eligible_voter_terms" : {
            "USING" : { "vote" : [ "node" ] },
            "PROVIDE" : { "terms" : { "terms" : "Terms" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "terms" ] },
            "ITEM" : { "term" : "Current term" },
            "DO" : [
              { "component_rules_voting_create_term_token" : {
                  "USING" : {
                    "vote" : [ "node-unchanged" ],
                    "term" : [ "term" ],
                    "secret_token" : [ "secret_token" ]
                  },
                  "PROVIDE" : { "success" : { "success" : "success" } }
                }
              }
            ]
          }
        },
        { "component_rules_voting_get_eligible_voter_users" : {
            "USING" : { "vote" : [ "node" ] },
            "PROVIDE" : { "users" : { "users" : "Users" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "user" : "Current user" },
            "DO" : [
              { "component_rules_voting_create_user_token" : {
                  "USING" : {
                    "vote" : [ "node-unchanged" ],
                    "user" : [ "user" ],
                    "secret_token" : [ "secret_token" ]
                  },
                  "PROVIDE" : { "success" : { "success" : "success" } }
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_voting_create_term_token'] = entity_import('rules_config', '{ "rules_voting_create_term_token" : {
      "LABEL" : "Create term token",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Secret Voting" ],
      "REQUIRES" : [ "rules", "secret_voting" ],
      "USES VARIABLES" : {
        "vote" : { "label" : "Vote node", "type" : "node" },
        "term" : { "label" : "voting term", "type" : "taxonomy_term" },
        "secret_token" : { "label" : "Secret token", "type" : "text" },
        "success" : { "label" : "success", "type" : "boolean", "parameter" : false }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "data_is" : { "data" : [ "vote:field-vote-secret" ], "value" : 1 } },
        { "entity_is_of_bundle" : {
            "entity" : [ "term" ],
            "type" : "taxonomy_term",
            "bundle" : { "value" : { "voting_terms" : "voting_terms" } }
          }
        },
        { "NOT voting_term_token_exists" : { "vote" : [ "vote" ], "term" : [ "term" ] } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : { "type" : "vote_token", "param_type" : "taxonomy_token" },
            "PROVIDE" : { "entity_created" : { "term_token" : "Created entity" } }
          }
        },
        { "data_set" : { "data" : [ "term-token:field-token-term" ], "value" : [ "term" ] } },
        { "data_set" : { "data" : [ "term-token:field-token-vote" ], "value" : [ "vote" ] } },
        { "voting_make_token_hash" : {
            "USING" : { "token" : [ "secret-token" ], "vote_token" : [ "term-token" ] },
            "PROVIDE" : { "token_hash" : { "token_hash" : "Token hash" } }
          }
        },
        { "data_set" : { "data" : [ "term-token:field-token-hash" ], "value" : [ "token-hash" ] } },
        { "entity_save" : { "data" : [ "term-token" ] } },
        { "data_set" : { "data" : [ "success" ], "value" : 1 } }
      ],
      "PROVIDES VARIABLES" : [ "success" ]
    }
  }');
  $items['rules_voting_create_user_token'] = entity_import('rules_config', '{ "rules_voting_create_user_token" : {
      "LABEL" : "Create user token",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Secret Voting" ],
      "REQUIRES" : [ "rules", "secret_voting" ],
      "USES VARIABLES" : {
        "vote" : { "label" : "Vote node", "type" : "node" },
        "user" : { "label" : "voting user", "type" : "user" },
        "secret_token" : { "label" : "Secret token", "type" : "text" },
        "success" : { "label" : "success", "type" : "boolean", "parameter" : false }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "NOT voting_user_token_exists" : { "vote" : [ "vote" ], "user" : [ "user" ] } },
        { "data_is" : { "data" : [ "vote:field-vote-secret" ], "value" : 1 } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : { "type" : "vote_token", "param_type" : "user_token" },
            "PROVIDE" : { "entity_created" : { "user_token" : "Created entity" } }
          }
        },
        { "data_set" : { "data" : [ "user-token:field-token-vote" ], "value" : [ "vote" ] } },
        { "data_set" : { "data" : [ "user-token:field-token-user" ], "value" : [ "user" ] } },
        { "voting_make_token_hash" : {
            "USING" : { "token" : [ "secret-token" ], "vote_token" : [ "user-token" ] },
            "PROVIDE" : { "token_hash" : { "token_hash" : "Token hash" } }
          }
        },
        { "data_set" : { "data" : [ "user-token:field-token-hash" ], "value" : [ "token-hash" ] } },
        { "entity_save" : { "data" : [ "user-token" ] } },
        { "data_set" : { "data" : [ "success" ], "value" : 1 } }
      ],
      "PROVIDES VARIABLES" : [ "success" ]
    }
  }');
  $items['rules_voting_get_eligible_voter_terms'] = entity_import('rules_config', '{ "rules_voting_get_eligible_voter_terms" : {
      "LABEL" : "get eligible voter terms",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Secret Voting" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "vote" : { "label" : "Vote", "type" : "node" },
        "terms" : {
          "label" : "Terms",
          "type" : "list\\u003Ctaxonomy_term\\u003E",
          "parameter" : false
        }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "data_is" : { "data" : [ "vote:field-vote-type" ], "value" : "taxonomy" } }
      ],
      "DO" : [
        { "data_set" : { "data" : [ "terms" ], "value" : [ "vote:field-vote-terms" ] } }
      ],
      "PROVIDES VARIABLES" : [ "terms" ]
    }
  }');
  $items['rules_voting_get_eligible_voter_users'] = entity_import('rules_config', '{ "rules_voting_get_eligible_voter_users" : {
      "LABEL" : "get eligible voter users",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Secret Voting" ],
      "REQUIRES" : [ "rules", "secret_voting" ],
      "USES VARIABLES" : {
        "vote" : { "label" : "Vote", "type" : "node" },
        "users" : {
          "label" : "Users",
          "type" : "list\\u003Cuser\\u003E",
          "parameter" : false
        }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "data_is" : { "data" : [ "vote:field-vote-type" ], "value" : "user" } }
      ],
      "DO" : [
        { "voting_get_users_of_roles" : {
            "USING" : { "role" : [ "vote:field-vote-roles" ] },
            "PROVIDE" : { "users" : { "roles_users" : "Users" } }
          }
        },
        { "data_set" : { "data" : [ "users" ], "value" : [ "roles-users" ] } }
      ],
      "PROVIDES VARIABLES" : [ "users" ]
    }
  }');
  $items['rules_voting_get_emails_from_token'] = entity_import('rules_config', '{ "rules_voting_get_emails_from_token" : {
      "LABEL" : "get emails from token",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Voting" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "term" : { "label" : "Term", "type" : "taxonomy_term" },
        "emails" : {
          "label" : "Emails",
          "type" : "list\\u003Ctext\\u003E",
          "parameter" : false
        }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "term" ],
            "type" : "taxonomy_term",
            "bundle" : { "value" : { "voting_terms" : "voting_terms" } }
          }
        }
      ],
      "DO" : [
        { "data_set" : { "data" : [ "emails" ], "value" : [ "term:field-voting-term-email" ] } }
      ],
      "PROVIDES VARIABLES" : [ "emails" ]
    }
  }');
  $items['rules_voting_inhibit_ongoing_vote_change'] = entity_import('rules_config', '{ "rules_voting_inhibit_ongoing_vote_change" : {
      "LABEL" : "Inhibit ongoing vote change",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Secret Voting" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_presave--vote" : { "bundle" : "vote" } },
      "IF" : [
        { "NOT data_is" : { "data" : [ "node:field-vote-state" ], "value" : "open" } },
        { "NOT data_is" : { "data" : [ "node-unchanged:field-vote-state" ], "value" : "open" } }
      ],
      "DO" : [
        { "data_set" : {
            "data" : [ "node:field-vote" ],
            "value" : [ "node-unchanged:field-vote" ]
          }
        },
        { "data_set" : {
            "data" : [ "node:field-vote-type" ],
            "value" : [ "node-unchanged:field-vote-type" ]
          }
        },
        { "data_set" : {
            "data" : [ "node:field-vote-terms" ],
            "value" : [ "node-unchanged:field-vote-terms" ]
          }
        },
        { "data_set" : {
            "data" : [ "node:field-vote-roles" ],
            "value" : [ "node-unchanged:field-vote-roles" ]
          }
        },
        { "data_set" : {
            "data" : [ "node:field-vote-secret" ],
            "value" : [ "node-unchanged:field-vote-secret" ]
          }
        },
        { "drupal_message" : { "message" : "An ongoing vote can not be changed!", "type" : "warning" } }
      ]
    }
  }');
  $items['rules_voting_invite_voters'] = entity_import('rules_config', '{ "rules_voting_invite_voters" : {
      "LABEL" : "Invite voters (private)",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Secret Voting" ],
      "REQUIRES" : [ "rules", "secret_voting", "rules_conditional" ],
      "USES VARIABLES" : { "vote" : { "label" : "Vote", "type" : "node" } },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "NOT data_is" : { "data" : [ "vote:field-vote-state" ], "value" : "closed" } },
        { "data_is" : { "data" : [ "vote:field-vote-secret" ], "value" : 1 } }
      ],
      "DO" : [
        { "component_rules_voting_get_eligible_voter_terms" : {
            "USING" : { "vote" : [ "vote" ] },
            "PROVIDE" : { "terms" : { "terms" : "Terms" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "terms" ] },
            "ITEM" : { "current_term" : "Current term" },
            "DO" : [
              { "voting_generate_token" : { "PROVIDE" : { "secret_token" : { "secret_token" : "Secret token" } } } },
              { "component_rules_voting_create_term_token" : {
                  "USING" : {
                    "vote" : [ "vote" ],
                    "term" : [ "current-term" ],
                    "secret_token" : [ "secret_token" ]
                  },
                  "PROVIDE" : { "success" : { "success" : "success" } }
                }
              },
              { "CONDITIONAL" : [
                  {
                    "IF" : { "data_is" : { "data" : [ "success" ], "value" : 1 } },
                    "DO" : [
                      { "component_rules_voting_get_emails_from_token" : {
                          "USING" : { "term" : [ "current-term" ] },
                          "PROVIDE" : { "emails" : { "emails" : "Emails" } }
                        }
                      },
                      { "LOOP" : {
                          "USING" : { "list" : [ "emails" ] },
                          "ITEM" : { "email" : "Current email" },
                          "DO" : [
                            { "component_rules_voting_send_token_via_email" : {
                                "vote" : [ "vote" ],
                                "email" : [ "email" ],
                                "token" : [ "secret-token" ]
                              }
                            }
                          ]
                        }
                      }
                    ]
                  }
                ]
              }
            ]
          }
        },
        { "component_rules_voting_get_eligible_voter_users" : {
            "USING" : { "vote" : [ "vote" ] },
            "PROVIDE" : { "users" : { "users" : "Users" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "user" : "Current user" },
            "DO" : [
              { "voting_generate_token" : { "PROVIDE" : { "secret_token" : { "secret_token" : "Secret token" } } } },
              { "component_rules_voting_create_user_token" : {
                  "USING" : {
                    "vote" : [ "vote" ],
                    "user" : [ "user" ],
                    "secret_token" : [ "secret_token" ]
                  },
                  "PROVIDE" : { "success" : { "success" : "success" } }
                }
              },
              { "CONDITIONAL" : [
                  {
                    "IF" : { "data_is" : { "data" : [ "success" ], "value" : 1 } },
                    "DO" : [
                      { "component_rules_voting_send_token_via_email" : {
                          "vote" : [ "vote" ],
                          "email" : [ "user:mail" ],
                          "token" : [ "secret-token" ]
                        }
                      }
                    ]
                  }
                ]
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_voting_register_vote'] = entity_import('rules_config', '{ "rules_voting_register_vote" : {
      "LABEL" : "Register Vote",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Secret Voting" ],
      "REQUIRES" : [ "rules", "secret_voting" ],
      "USES VARIABLES" : {
        "vote" : { "label" : "Vote", "type" : "node" },
        "secret_token" : { "label" : "Secret Token", "type" : "text" },
        "answer" : {
          "label" : "Answer",
          "type" : "list\\u003Csecret_voting_field_answer\\u003E"
        },
        "success" : { "label" : "success", "type" : "boolean", "parameter" : false }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "data_is" : { "data" : [ "vote:field-vote-secret" ], "value" : 1 } },
        { "voting_vote_answer_makes_sense" : { "vote" : [ "vote" ], "answer" : [ "answer" ] } },
        { "NOT voting_ballot_exists" : { "vote" : [ "vote" ], "secret_token" : [ "secret_token" ] } },
        { "voting_secret_valid" : { "vote" : [ "vote" ], "secret_token" : [ "secret_token" ] } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : { "type" : "vote_ballot", "param_type" : "vote_ballot" },
            "PROVIDE" : { "entity_created" : { "vote_ballot" : "Ballot" } }
          }
        },
        { "data_set" : { "data" : [ "vote-ballot:field-ballot-answer" ], "value" : [ "answer" ] } },
        { "data_set" : { "data" : [ "vote-ballot:field-token-vote" ], "value" : [ "vote" ] } },
        { "voting_make_node_hash" : {
            "USING" : { "token" : [ "secret-token" ], "vote" : [ "vote" ] },
            "PROVIDE" : { "node_hash" : { "node_hash" : "Node hash" } }
          }
        },
        { "data_set" : { "data" : [ "vote-ballot:field-token-hash" ], "value" : [ "node-hash" ] } },
        { "entity_save" : { "data" : [ "vote-ballot" ] } },
        { "data_set" : { "data" : [ "success" ], "value" : 1 } }
      ],
      "PROVIDES VARIABLES" : [ "success" ]
    }
  }');
  $items['rules_voting_send_token_via_email'] = entity_import('rules_config', '{ "rules_voting_send_token_via_email" : {
      "LABEL" : "Send token via email",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Secret Voting" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "vote" : { "label" : "Vote", "type" : "node" },
        "email" : { "label" : "Email", "type" : "text" },
        "token" : { "label" : "Token", "type" : "text" }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "email" ],
            "subject" : "[site:name] - Secret vote for [vote:title]",
            "message" : "Hello,\\r\\n\\r\\nA voting token has been generated for you: [token:value]\\r\\nEnter it on the voting site: [vote:url]\\r\\nOr go to the voting directly by going to: [site:url]node\\/[vote:nid]\\/vote\\/[token:value]\\r\\nThe voting ends on: [vote:field_vote_closing_date]\\r\\n\\r\\nThank you for your participation.",
            "from" : [ "site:mail" ],
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['secret_voting_change_vote_state_when_voting_public'] = entity_import('rules_config', '{ "secret_voting_change_vote_state_when_voting_public" : {
      "LABEL" : "Change Vote state when voting public",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Voting" ],
      "REQUIRES" : [ "rules", "eck" ],
      "ON" : { "vote_ballot_insert" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "vote-ballot" ], "field" : "field_token_vote" } },
        { "entity_is_of_bundle" : {
            "entity" : [ "vote-ballot:field-token-vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "data_is" : {
            "data" : [ "vote-ballot:field-token-vote:field-vote-state" ],
            "value" : "open"
          }
        }
      ],
      "DO" : [
        { "data_set" : {
            "data" : [ "vote-ballot:field-token-vote:field-vote-state" ],
            "value" : "ongoing"
          }
        },
        { "entity_save" : { "data" : [ "vote-ballot:field-token-vote" ] } }
      ]
    }
  }');
  $items['secret_voting_invite_voters_public'] = entity_import('rules_config', '{ "secret_voting_invite_voters_public" : {
      "LABEL" : "Invite voters (public)",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Voting" ],
      "REQUIRES" : [ "rules", "secret_voting" ],
      "USES VARIABLES" : { "vote" : { "label" : "Vote", "type" : "node" } },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "NOT data_is" : { "data" : [ "vote:field-vote-state" ], "value" : "closed" } },
        { "data_is" : { "data" : [ "vote:field-vote-secret" ], "value" : 0 } }
      ],
      "DO" : [
        { "component_rules_voting_get_eligible_voter_terms" : {
            "USING" : { "vote" : [ "vote" ] },
            "PROVIDE" : { "terms" : { "terms" : "Terms" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "terms" ] },
            "ITEM" : { "current_term" : "Current term" },
            "DO" : [
              { "component_rules_voting_get_emails_from_token" : {
                  "USING" : { "term" : [ "current-term" ] },
                  "PROVIDE" : { "emails" : { "emails" : "Emails" } }
                }
              },
              { "LOOP" : {
                  "USING" : { "list" : [ "emails" ] },
                  "ITEM" : { "email" : "Current email" },
                  "DO" : [
                    { "component_secret_voting_send_public_invitation_via_email" : { "vote" : [ "vote" ], "email" : [ "email" ] } }
                  ]
                }
              }
            ]
          }
        },
        { "component_rules_voting_get_eligible_voter_users" : {
            "USING" : { "vote" : [ "vote" ] },
            "PROVIDE" : { "users" : { "users" : "Users" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "user" : "Current user" },
            "DO" : [
              { "voting_generate_token" : { "PROVIDE" : { "secret_token" : { "secret_token" : "Secret token" } } } },
              { "component_secret_voting_send_public_invitation_via_email" : { "vote" : [ "vote" ], "email" : [ "user:mail" ] } }
            ]
          }
        }
      ]
    }
  }');
  $items['secret_voting_register_vote_term'] = entity_import('rules_config', '{ "secret_voting_register_vote_term" : {
      "LABEL" : "Register Vote (term)",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Voting" ],
      "REQUIRES" : [ "rules", "secret_voting" ],
      "USES VARIABLES" : {
        "vote" : { "label" : "Vote", "type" : "node" },
        "term" : { "label" : "Term", "type" : "taxonomy_term" },
        "answer" : {
          "label" : "Answer",
          "type" : "list\\u003Csecret_voting_field_answer\\u003E"
        },
        "success" : { "label" : "success", "type" : "boolean", "parameter" : false }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "data_is" : { "data" : [ "vote:field-vote-secret" ], "value" : 0 } },
        { "voting_vote_answer_makes_sense" : { "vote" : [ "vote" ], "answer" : [ "answer" ] } },
        { "NOT voting_term_ballot_exists" : { "vote" : [ "vote" ], "term" : [ "term" ] } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : { "type" : "vote_ballot", "param_type" : "term_ballot" },
            "PROVIDE" : { "entity_created" : { "vote_ballot" : "Ballot" } }
          }
        },
        { "data_set" : { "data" : [ "vote-ballot:field-ballot-answer" ], "value" : [ "answer" ] } },
        { "data_set" : { "data" : [ "vote-ballot:field-token-vote" ], "value" : [ "vote" ] } },
        { "data_set" : { "data" : [ "vote-ballot:field-token-term" ], "value" : [ "term" ] } },
        { "entity_save" : { "data" : [ "vote-ballot" ] } },
        { "data_set" : { "data" : [ "success" ], "value" : 1 } }
      ],
      "PROVIDES VARIABLES" : [ "success" ]
    }
  }');
  $items['secret_voting_secret_voting_register_vote_user'] = entity_import('rules_config', '{ "secret_voting_secret_voting_register_vote_user" : {
      "LABEL" : "Register Vote (user)",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Voting" ],
      "REQUIRES" : [ "rules", "secret_voting" ],
      "USES VARIABLES" : {
        "vote" : { "label" : "Vote", "type" : "node" },
        "user" : { "label" : "User", "type" : "user" },
        "answer" : {
          "label" : "Answer",
          "type" : "list\\u003Csecret_voting_field_answer\\u003E"
        },
        "success" : { "label" : "success", "type" : "boolean", "parameter" : false }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        },
        { "data_is" : { "data" : [ "vote:field-vote-secret" ], "value" : 0 } },
        { "voting_vote_answer_makes_sense" : { "vote" : [ "vote" ], "answer" : [ "answer" ] } },
        { "NOT voting_user_ballot_exists" : { "vote" : [ "vote" ], "user" : [ "user" ] } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : { "type" : "vote_ballot", "param_type" : "user_ballot" },
            "PROVIDE" : { "entity_created" : { "vote_ballot" : "Ballot" } }
          }
        },
        { "data_set" : { "data" : [ "vote-ballot:field-ballot-answer" ], "value" : [ "answer" ] } },
        { "data_set" : { "data" : [ "vote-ballot:field-token-vote" ], "value" : [ "vote" ] } },
        { "data_set" : { "data" : [ "vote-ballot:field-token-user" ], "value" : [ "user" ] } },
        { "entity_save" : { "data" : [ "vote-ballot" ] } },
        { "data_set" : { "data" : [ "success" ], "value" : 1 } }
      ],
      "PROVIDES VARIABLES" : [ "success" ]
    }
  }');
  $items['secret_voting_send_public_invitation_via_email'] = entity_import('rules_config', '{ "secret_voting_send_public_invitation_via_email" : {
      "LABEL" : "Send public invitation via email",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Voting" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "vote" : { "label" : "Vote", "type" : "node" },
        "email" : { "label" : "Email", "type" : "text" }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "vote" ],
            "type" : "node",
            "bundle" : { "value" : { "vote" : "vote" } }
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "email" ],
            "subject" : "[site:name] - Public vote for [vote:title]",
            "message" : "Hello,\\r\\n\\r\\nA public vote has been set up.\\r\\nVote on: [vote:url]\\r\\nOr go to the voting directly by going to: [site:url]node\\/[vote:nid]\\/vote\\r\\nThe voting ends on: [vote:field_vote_closing_date]\\r\\n\\r\\nThank you for your participation.",
            "from" : [ "site:mail" ],
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
